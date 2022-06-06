#ifndef LOGGING_H
#define LOGGING_H

#ifdef __cplusplus
extern "C" {
#endif

void OpenNetworkNotifications(void);
void CloseNetworkHandles(void);
void ServerLog(const char *str);
void CloseLogChannel(void);
int NotificationIRQRaised(void);
void ClearNotificationIRQ(void);
void HandleIRQ(void);

#ifdef __cplusplus
}
#endif

#endif /* LOGGING_H */
