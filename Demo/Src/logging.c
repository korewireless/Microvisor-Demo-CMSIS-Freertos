#include <string.h>

#include "logging.h"
#include "stm32u5xx_hal.h"
#include "mv_syscalls.h"

struct {
    MvNotificationHandle notification;
    MvNetworkHandle network;
    MvChannelHandle channel;
} log_handles = { 0, 0, 0 };

static volatile struct MvNotification log_notification_buffer[16];

// arbitrary user specified uint32_t tags for any notifications from mv calls supporting notifications:
const uint32_t USER_TAG_LOGGING_REQUEST_NETWORK = 1;
const uint32_t USER_TAG_LOGGING_OPEN_CHANNEL = 2;

void TIM8_BRK_IRQHandler(void)
{
    // You can handle events here
}

void OpenLogChannel(void)
{
    memset((void *)log_notification_buffer, 0xff, sizeof(log_notification_buffer));
    static struct MvNotificationSetup setup = {
        .irq = TIM8_BRK_IRQn,
        .buffer = (struct MvNotification *)log_notification_buffer,
        .buffer_size = sizeof(log_notification_buffer)
    };
    uint32_t status = mvSetupNotifications(&setup, &log_handles.notification);
    assert(status == MV_STATUS_OKAY);

    NVIC_ClearPendingIRQ(TIM8_BRK_IRQn);
    NVIC_EnableIRQ(TIM8_BRK_IRQn);

    struct MvRequestNetworkParams nw_params = {
        .version = 1,
        .v1 = {
            .notification_handle = log_handles.notification,
            .notification_tag = USER_TAG_LOGGING_REQUEST_NETWORK,
        }
    };
    status = mvRequestNetwork(&nw_params, &log_handles.network);
    assert(status == MV_STATUS_OKAY);

    static volatile uint8_t receive_buffer[16];
    static volatile uint8_t send_buffer[512] __attribute__((aligned(512)));
    char endpoint[] = "log";
    struct MvOpenChannelParams ch_params = {
        .version = 1,
        .v1 = {
            .notification_handle = log_handles.notification,
            .notification_tag = USER_TAG_LOGGING_OPEN_CHANNEL,
            .network_handle = log_handles.network,
            .receive_buffer = (uint8_t*)receive_buffer,
            .receive_buffer_len = sizeof(receive_buffer),
            .send_buffer = (uint8_t*)send_buffer,
            .send_buffer_len = sizeof(send_buffer),
            .channel_type = MV_CHANNELTYPE_OPAQUEBYTES,
            .endpoint = (uint8_t*)endpoint,
            .endpoint_len = strlen(endpoint)
        }
    };

    while (1) {  // busy wait for connection
        enum MvNetworkStatus status;
        if (mvGetNetworkStatus(log_handles.network, &status) == MV_STATUS_OKAY &&
            status == MV_NETWORKSTATUS_CONNECTED) {
            break;
        }
        for (volatile unsigned i = 0; i < 50000; i++) {} // busy delay
    }

    status = mvOpenChannel(&ch_params, &log_handles.channel);
    assert(status == MV_STATUS_OKAY);
}

void CloseLogChannel(void)
{
    if (log_handles.channel != 0) {
      uint32_t status = mvCloseChannel(&log_handles.channel);
      assert(status == MV_STATUS_OKAY);
    }
    assert(log_handles.channel == 0);
    if (log_handles.network != 0) {
      uint32_t status = mvReleaseNetwork(&log_handles.network);
      assert(status == MV_STATUS_OKAY);
    }
    assert(log_handles.network == 0);
    if (log_handles.notification != 0) {
      uint32_t status = mvCloseNotifications(&log_handles.notification);
      assert(status == MV_STATUS_OKAY);
    }
    assert(log_handles.notification == 0);

    NVIC_DisableIRQ(TIM8_BRK_IRQn);
    NVIC_ClearPendingIRQ(TIM8_BRK_IRQn);
}

void ServerLog(const char *str)
{
    if (log_handles.channel == 0) {
        OpenLogChannel();
    }
    uint32_t available, status;
    status = mvWriteChannel(log_handles.channel, (const uint8_t*)str, strlen(str), &available);
    assert(status == MV_STATUS_OKAY);
    status = mvWriteChannel(log_handles.channel, (const uint8_t*)"\n", 1, &available);
    assert(status == MV_STATUS_OKAY);
}
