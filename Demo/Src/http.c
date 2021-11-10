#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#include "logging.h"
#include "stm32u5xx_hal.h"
#include "mv_syscalls.h"

#define MAX_NOTIFICATIONS 16

struct {
    MvNotificationHandle notification;
    MvNetworkHandle network;
    MvChannelHandle channel;
} http_handles = { 0, 0, 0 };

static volatile struct MvNotification http_notification_buffer[MAX_NOTIFICATIONS];
static volatile int notify_read_ind = 0;

const uint32_t USER_TAG_HTTP_REQUEST_NETWORK = 1;
const uint32_t USER_TAG_HTTP_OPEN_CHANNEL = 2;

void TIM8_UP_IRQHandler(void)
{
    // You can handle events here
}

static volatile struct MvNotification *next_notification(void)
{
    while (http_notification_buffer[notify_read_ind].event_type == 0)
    {
        __asm ("wfi");
    }

    volatile struct MvNotification* ret = &http_notification_buffer[notify_read_ind];
    notify_read_ind = (notify_read_ind + 1 ) % MAX_NOTIFICATIONS;
    return ret;
}

static void wait_for_notification(const enum MvEventType type, const uint32_t event_tag)
{
    while (1)
    {
        volatile struct MvNotification *n = next_notification();
        if (n->event_type == type && n->tag == event_tag)
        {
            printf("Done waiting for %08lx:%08lx\n", (long)type, (long)event_tag);
            return;
        }
        printf("got notification %08lx:%08lx, waiting for %08lx:%08lx",
                        (long)n->event_type, (long)n->tag,
                        (long)type, (long)event_tag);
    }
}

static void OpenHttpChannel()
{
    memset((void *)http_notification_buffer, 0x00, sizeof(http_notification_buffer));
    static struct MvNotificationSetup setup = {
        .irq = TIM8_UP_IRQn,
        .buffer = (struct MvNotification *)http_notification_buffer,
        .buffer_size = sizeof(http_notification_buffer)
    };
    memset((void *)http_notification_buffer, 0, sizeof(http_notification_buffer));
    uint32_t status = mvSetupNotifications(&setup, &http_handles.notification);
    assert(status == MV_STATUS_OKAY);

    NVIC_ClearPendingIRQ(TIM8_UP_IRQn);
    NVIC_EnableIRQ(TIM8_UP_IRQn);

    struct MvRequestNetworkParams nw_params = {
        .version = 1,
        .v1 = {
            .notification_handle = http_handles.notification,
            .notification_tag = USER_TAG_HTTP_REQUEST_NETWORK,
        }
    };
    status = mvRequestNetwork(&nw_params, &http_handles.network);
    assert(status == MV_STATUS_OKAY);

    static volatile uint8_t receive_buffer[4096] __attribute__((aligned(512)));
    static volatile uint8_t send_buffer[1024] __attribute__((aligned(512)));
    struct MvOpenChannelParams ch_params = {
        .version = 1,
        .v1 = {
            .notification_handle = http_handles.notification,
            .notification_tag = USER_TAG_HTTP_OPEN_CHANNEL,
            .network_handle = http_handles.network,
            .receive_buffer = (uint8_t*)receive_buffer,
            .receive_buffer_len = sizeof(receive_buffer),
            .send_buffer = (uint8_t*)send_buffer,
            .send_buffer_len = sizeof(send_buffer),
            .channel_type = MV_CHANNELTYPE_HTTP,
            .endpoint = (uint8_t*)"",
            .endpoint_len = 0
        }
    };

    while (1) {  // busy wait for connection
        enum MvNetworkStatus status;
        if (mvGetNetworkStatus(http_handles.network, &status) == MV_STATUS_OKAY &&
            status == MV_NETWORKSTATUS_CONNECTED) {
            break;
        }
        for (volatile unsigned i = 0; i < 50000; i++) {} // busy delay
    }

    status = mvOpenChannel(&ch_params, &http_handles.channel);
    assert(status == MV_STATUS_OKAY);
}

static void CloseHttpChannel(void)
{
    if (http_handles.channel != 0) {
      uint32_t status = mvCloseChannel(&http_handles.channel);
      assert(status == MV_STATUS_OKAY);
    }
    assert(http_handles.channel == 0);
    if (http_handles.network != 0) {
      uint32_t status = mvReleaseNetwork(&http_handles.network);
      assert(status == MV_STATUS_OKAY);
    }
    assert(http_handles.network == 0);
    if (http_handles.notification != 0) {
      uint32_t status = mvCloseNotifications(&http_handles.notification);
      assert(status == MV_STATUS_OKAY);
    }
    assert(http_handles.notification == 0);

    NVIC_DisableIRQ(TIM8_UP_IRQn);
    NVIC_ClearPendingIRQ(TIM8_UP_IRQn);
}

enum MvStatus SendHttpRequest(const struct MvHttpRequest *request)
{
    OpenHttpChannel();
    uint32_t status = mvSendHttpRequest(http_handles.channel, request);

    return status;
}

void WaitForHttpResponse()
{
    wait_for_notification(MV_EVENTTYPE_CHANNELDATAREADABLE, USER_TAG_HTTP_OPEN_CHANNEL);    
}

enum MvStatus GetHttpResponseData(struct MvHttpResponseData *responseData)
{
    return mvReadHttpResponseData(http_handles.channel, responseData);
}

enum MvStatus GetHttpResponseHeader(uint32_t header_index, uint8_t *buf, uint32_t size)
{
    return mvReadHttpResponseHeader(http_handles.channel, header_index, buf, size);
}

enum MvStatus GetHttpResponseBody(uint32_t offset, uint8_t *buf, uint32_t size)
{
    return mvReadHttpResponseBody(http_handles.channel, offset, buf, size);
}

void FinishedWithHttpResponse()
{
    CloseHttpChannel();
}
