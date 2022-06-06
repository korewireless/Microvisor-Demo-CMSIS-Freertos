/**
    Twilio Microvisor FreeRTOS Demo

    Copyright © 2021, Twilio
    License: Apache 2.0

 */
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#include "logging.h"
#include "stm32u5xx_hal.h"
#include "mv_syscalls.h"


// Central store for Microvisor resource handles used in this code.
// See 'https://www.twilio.com/docs/iot/microvisor/syscalls#handles'
struct {
    MvNotificationHandle notification;
    MvNetworkHandle      network;
    MvChannelHandle      channel;
} log_handles = { 0, 0, 0 };

// Central store for notification records. Holds one record at
// a time -- each record is 16 bytes in size.
#define NOTIFICATION_BUFFER_SIZE 16
static volatile struct MvNotification log_notification_buffer[NOTIFICATION_BUFFER_SIZE];

// Arbitrary user-specified uint32_t tags for any notifications
// from Microvisor calls that support notifications:
const uint32_t USER_TAG_LOGGING_REQUEST_NETWORK = 1;
const uint32_t USER_TAG_LOGGING_OPEN_CHANNEL    = 2;

static uint32_t buffer_pos;
static int readOne(uint32_t type, struct MvNotification *n)
{
    volatile struct MvNotification *notification = &log_notification_buffer[buffer_pos];
    if (notification->microseconds != 0 &&
        notification->event_type == type) {
            n->microseconds = notification->microseconds;
            n->event_type = notification->event_type;
            n->tag = notification->tag;
            notification->event_type = 0;
            buffer_pos += 1;
            if (buffer_pos >= NOTIFICATION_BUFFER_SIZE) {
                buffer_pos = 0;
            }
            return 1;
    }
    return 0;
}

static struct MvNotificationSetup notification_center_setup;
struct MvRequestNetworkParams network_params;
// Set up the channel's send and receive buffers
static volatile uint8_t receive_buffer[16];
static volatile uint8_t send_buffer[512] __attribute__((aligned(512)));
uint8_t endpoint[] = { 'l', 'o', 'g' };
static struct MvOpenChannelParams channel_params;
volatile int irqHappened = 0;

void OpenLogChannel(void)
{
    enum MvNetworkStatus netstat;
    assert(MV_STATUS_OKAY == mvGetNetworkStatus(log_handles.network, &netstat));
    if (netstat == MV_NETWORKSTATUS_CONNECTED) {
        // Configure the required data channel
        channel_params.version = 1,
        channel_params.v1.notification_handle = log_handles.notification;
        channel_params.v1.notification_tag    = USER_TAG_LOGGING_OPEN_CHANNEL;
        channel_params.v1.network_handle      = log_handles.network;
        channel_params.v1.receive_buffer      = (uint8_t*)receive_buffer;
        channel_params.v1.receive_buffer_len  = sizeof(receive_buffer);
        channel_params.v1.send_buffer         = (uint8_t*)send_buffer;
        channel_params.v1.send_buffer_len     = sizeof(send_buffer);
        channel_params.v1.channel_type        = MV_CHANNELTYPE_OPAQUEBYTES;
        channel_params.v1.endpoint            = (uint8_t*)endpoint;
        channel_params.v1.endpoint_len        = sizeof(endpoint);
        uint32_t status = mvOpenChannel(&channel_params, &log_handles.channel);
        assert(status == MV_STATUS_OKAY);
    }
}

void CloseLogChannel(void)
{
    if (log_handles.channel != 0) {
        uint32_t status = mvCloseChannel(&log_handles.channel);
        assert(status == MV_STATUS_OKAY);
    }
    assert(log_handles.channel == 0);
}

void TIM8_BRK_IRQHandler(void) {
    // You can handle events here
    irqHappened = 1;
}

static void TIM8_BRK_DSR(struct MvOpenChannelParams *channel_params)
{
    struct MvNotification notification;
    while (readOne(MV_EVENTTYPE_NETWORKSTATUSCHANGED, &notification)) {
        enum MvNetworkStatus netstat;
        if (notification.tag == USER_TAG_LOGGING_REQUEST_NETWORK) {
            assert(MV_STATUS_OKAY == mvGetNetworkStatus(log_handles.network, &netstat));
        }
        switch (netstat) {
            case MV_NETWORKSTATUS_CONNECTED:
                break;
            default:
            case MV_NETWORKSTATUS_CONNECTING:
            case MV_NETWORKSTATUS_DELIBERATELYOFFLINE:
                CloseLogChannel();
                break;
        }
    }
}

int NotificationIRQRaised(void)
{
    return irqHappened;
}

void ClearNotificationIRQ(void)
{
    irqHappened = 0;
}

void HandleIRQ(void)
{
    TIM8_BRK_DSR(&channel_params);
}

/**
    @brief  Open a logging channel.

    Open a data channel for Microvisor logging.
    This call will also request a network connection.
 */
void OpenNetworkNotifications(void) {
    // Clear the notification store
    memset((void *)log_notification_buffer, 0xFF, sizeof(log_notification_buffer));
    buffer_pos = 0;

    // Configure a notification center for network-centric notifications
    notification_center_setup.irq = TIM8_BRK_IRQn;
    notification_center_setup.buffer = (struct MvNotification *)log_notification_buffer;
    notification_center_setup.buffer_size = sizeof(log_notification_buffer);

    // Ask Microvisor to establish the notification center
    // and confirm that it has accepted the request
    uint32_t status = mvSetupNotifications(&notification_center_setup, &log_handles.notification);
    assert(status == MV_STATUS_OKAY);

    NVIC_ClearPendingIRQ(TIM8_BRK_IRQn);
    NVIC_EnableIRQ(TIM8_BRK_IRQn);

    // Configure the network connection request
    network_params.version = 1;
    network_params.v1.notification_handle = log_handles.notification;
    network_params.v1.notification_tag = USER_TAG_LOGGING_REQUEST_NETWORK;

    // Ask Microvisor to establish the network connection
    // and confirm that it has accepted the request
    status = mvRequestNetwork(&network_params, &log_handles.network);
    assert(status == MV_STATUS_OKAY);
}


/**
    @brief  Open the logging channel.

    Close the data channel -- and the network connection -- when
    we're done with it.
 */
void CloseNetworkHandles(void) {
    uint32_t status;

    // If we have a valid network handle, then ask Microvisor to
    // close the connection and confirm acceptance of the request.
    if (log_handles.network != 0) {
        status = mvReleaseNetwork(&log_handles.network);
        assert(status == MV_STATUS_OKAY);
    }

    // Confirm the network handle has been invalidated by Microvisor
    assert(log_handles.network == 0);

    // If we have a valid notification center handle, then ask Microvisor
    // to tear down the center and confirm acceptance of the request.
    if (log_handles.notification != 0) {
        status = mvCloseNotifications(&log_handles.notification);
        assert(status == MV_STATUS_OKAY);
    }

    // Confirm the notification center handle has been invalidated by Microvisor
    assert(log_handles.notification == 0);

    NVIC_DisableIRQ(TIM8_BRK_IRQn);
    NVIC_ClearPendingIRQ(TIM8_BRK_IRQn);
}


/**
    @brief  Send a log entry.

    Send a log message, opening a logging data channel if one
    is not already open.

    @param  message     The log entry -- a C string -- to send.
 */
void ServerLog(const char *message) {
    // Do we have an open channel? If not, any stored channel handle
    // will be invalid, ie. zero. If that's the case, open a channel
    if (log_handles.channel == 0) {
        OpenLogChannel();
        while (log_handles.channel == 0) {}
    }

    // Write out the message string and then send a convenient
    // carriage return too. Each time confirm that Microvisor has
    // accepted the request to write data to the channel.
    uint32_t available, status;
    status = mvWriteChannel(log_handles.channel, (const uint8_t*)message, strlen(message), &available);
    //assert(status == MV_STATUS_OKAY);
    status = mvWriteChannel(log_handles.channel, (const uint8_t*)"\n", 1, &available);
    //assert(status == MV_STATUS_OKAY);
}

/**
    Wire up the `stdio` system call, so that `printf()`
    works as a logging message generator.

    @param  file    The log entry -- a C string -- to send.
    @param  ptr     A pointer to the C string we want to send.
    @param  length  The length of the message.

    @return         The number of bytes written, or -1 to indicate error.
 */
int _write(int file, char *ptr, int length) {
    if (file != STDOUT_FILENO) {
        errno = EBADF;
        return -1;
    }

    // Do we have an open channel? If not, any stored channel handle
    // will be invalid, ie. zero. If that's the case, open a channel
    if (log_handles.channel == 0) {
        OpenLogChannel();
        while (log_handles.channel == 0) {}
    }

    // Write out the message string. Each time confirm that Microvisor
    // has accepted the request to write data to the channel.
    uint32_t written, status;
    status = mvWriteChannelStream(log_handles.channel, (const uint8_t*)ptr, length, &written);
    if (status == MV_STATUS_OKAY) {
        // Return the number of characters written
        // out to the channel
        return written;
    } else {
        errno = EIO;
        return -1;
    }
}
