#ifndef HTTP_H
#define HTTP_H

#include "mv_syscalls.h"

#ifdef __cplusplus
extern "C" {
#endif

enum MvStatus SendHttpRequest(const struct MvHttpRequest *request);
void WaitForHttpResponse();
enum MvStatus GetHttpResponseData(struct MvHttpResponseData *responseData);
enum MvStatus GetHttpResponseHeader(uint32_t header_index, uint8_t *buf, uint32_t size);
enum MvStatus GetHttpResponseBody(uint32_t offset, uint8_t *buf, uint32_t size);
void FinishedWithHttpResponse();

#ifdef __cplusplus
}
#endif

#endif /* HTTP_H */
