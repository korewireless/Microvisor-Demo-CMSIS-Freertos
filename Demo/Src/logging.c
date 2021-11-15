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
static volatile struct MvNotification log_notification_buffer[16];

// Arbitrary user-specified uint32_t tags for any notifications
// from Microvisor calls that support notifications:
const uint32_t USER_TAG_LOGGING_REQUEST_NETWORK = 1;
const uint32_t USER_TAG_LOGGING_OPEN_CHANNEL    = 2;


void TIM8_BRK_IRQHandler(void) {
    // You can handle events here
}


/**
    @brief  Open a logging channel.

    Open a data channel for Microvisor logging.
    This call will also request a network connection.
 */
void OpenLogChannel(void) {
    // Clear the notification store
    memset((void *)log_notification_buffer, 0xFF, sizeof(log_notification_buffer));

    // Configure a notification center for network-centric notifications
    static struct MvNotificationSetup notification_center_setup = {
        .irq = TIM8_BRK_IRQn,
        .buffer = (struct MvNotification *)log_notification_buffer,
        .buffer_size = sizeof(log_notification_buffer)
    };

    // Ask Microvisor to establish the notification center
    // and confirm that it has accepted the request
    uint32_t status = mvSetupNotifications(&notification_center_setup, &log_handles.notification);
    assert(status == MV_STATUS_OKAY);

    NVIC_ClearPendingIRQ(TIM8_BRK_IRQn);
    NVIC_EnableIRQ(TIM8_BRK_IRQn);

    // Configure the network connection request
    struct MvRequestNetworkParams network_params = {
        .version = 1,
        .v1 = {
            .notification_handle = log_handles.notification,
            .notification_tag = USER_TAG_LOGGING_REQUEST_NETWORK,
        }
    };

    // Ask Microvisor to establish the network connection
    // and confirm that it has accepted the request
    status = mvRequestNetwork(&network_params, &log_handles.network);
    assert(status == MV_STATUS_OKAY);

    // Set up the channel's send and receive buffers
    static volatile uint8_t receive_buffer[16];
    static volatile uint8_t send_buffer[512] __attribute__((aligned(512)));
    char endpoint[] = "log";

    // Configure the required data channel
    struct MvOpenChannelParams channel_params = {
        .version = 1,
        .v1 = {
            .notification_handle = log_handles.notification,
            .notification_tag    = USER_TAG_LOGGING_OPEN_CHANNEL,
            .network_handle      = log_handles.network,
            .receive_buffer      = (uint8_t*)receive_buffer,
            .receive_buffer_len  = sizeof(receive_buffer),
            .send_buffer         = (uint8_t*)send_buffer,
            .send_buffer_len     = sizeof(send_buffer),
            .channel_type        = MV_CHANNELTYPE_OPAQUEBYTES,
            .endpoint            = (uint8_t*)endpoint,
            .endpoint_len        = strlen(endpoint)
        }
    };

    // The network connection is established by Microvisor asynchronously,
    // so we wait for it to come up before opening the data channel -- which
    // would fail otherwise
    while (1) {
        enum MvNetworkStatus status;

        // Request the status of the network connection, identified by its handle.
        // If we're good to continue, break out of the loop...
        if (mvGetNetworkStatus(log_handles.network, &status) == MV_STATUS_OKAY &&
            status == MV_NETWORKSTATUS_CONNECTED) {
            break;
        }

        // ... or wait a short period before retrying
        for (volatile unsigned i = 0; i < 50000; i++) {
            // No op
            __asm("nop");
        }
    }

    // Ask Microvisor to open the channel
    // and confirm that it has accepted the request
    status = mvOpenChannel(&channel_params, &log_handles.channel);
    assert(status == MV_STATUS_OKAY);
}


/**
    @brief  Open the logging channel.

    Close the data channel -- and the network connection -- when
    we're done with it.
 */
void CloseLogChannel(void) {
    uint32_t status;

    // If we have a valid channel handle -- ie. it is non-zero --
    // then ask Microvisor to close it and confirm acceptance of
    // the closure request.
    if (log_handles.channel != 0) {
        status = mvCloseChannel(&log_handles.channel);
        assert(status == MV_STATUS_OKAY);
    }

    // Confirm the channel handle has been invalidated by Microvisor
    assert(log_handles.channel == 0);

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
    }

    // Write out the message string and then send a convenient
    // carriage return too. Each time confirm that Microvisor has
    // accepted the request to write data to the channel.
    uint32_t available, status;
    status = mvWriteChannel(log_handles.channel, (const uint8_t*)message, strlen(message), &available);
    assert(status == MV_STATUS_OKAY);
    status = mvWriteChannel(log_handles.channel, (const uint8_t*)"\n", 1, &available);
    assert(status == MV_STATUS_OKAY);
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
