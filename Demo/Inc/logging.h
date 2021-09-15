#ifndef __LOGGING_H
#define __LOGGING_H

#ifdef __cplusplus
extern "C" {
#endif

void ServerLog(const char *str);
void CloseLogChannel(void);

#ifdef __cplusplus
}
#endif

#endif /* __LOGGING_H */
