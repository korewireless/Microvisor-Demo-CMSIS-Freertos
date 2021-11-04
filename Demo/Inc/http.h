#ifndef HTTP_H
#define HTTP_H

#include "mv_syscalls.h"

#ifdef __cplusplus
extern "C" {
#endif

enum MvStatus SendHttpRequest(const struct MvHttpRequest *request);

#ifdef __cplusplus
}
#endif

#endif /* HTTP_H */
