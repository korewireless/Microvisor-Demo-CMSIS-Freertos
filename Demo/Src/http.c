#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#include "logging.h"
#include "stm32u5xx_hal.h"
#include "mv_syscalls.h"

struct {
    MvNotificationHandle notification;
    MvNetworkHandle network;
    MvChannelHandle channel;
} http_handles = { 0, 0, 0 };

static volatile struct MvNotification http_notification_buffer[16];

const uint32_t USER_TAG_HTTP_REQUEST_NETWORK = 1;
const uint32_t USER_TAG_HTTP_OPEN_CHANNEL = 2;

void TIM8_UP_IRQHandler(void)
{
    // You can handle events here
}

static void OpenHttpChannel()
{
    memset((void *)http_notification_buffer, 0x00, sizeof(http_notification_buffer));
    static struct MvNotificationSetup setup = {
        .irq = TIM8_UP_IRQn,
        .buffer = (struct MvNotification *)http_notification_buffer,
        .buffer_size = sizeof(http_notification_buffer)
    };
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

    static volatile uint8_t receive_buffer[512] __attribute__((aligned(512)));
    static volatile uint8_t send_buffer[512] __attribute__((aligned(512)));
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

    CloseHttpChannel();

    return status;
}
