#ifndef LOGGING_H
#define LOGGING_H

#ifdef __cplusplus
extern "C" {
#endif

void ServerLog(const char *str);
void CloseLogChannel(void);

#ifdef __cplusplus
}
#endif

#endif /* LOGGING_H */
