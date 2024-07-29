/*
 *
 * Microvisor FreeRTOS Demo
 *
 * Copyright © 2024, KORE Wireless
 * Licence: MIT
 *
 */
#ifndef MAIN_H
#define MAIN_H


#define     PING_PAUSE_MS               5000
#define     LED_PAUSE_MS                1000

#define     LOG_BUFFER_SIZE_B           5120
#define     LOG_MESSAGE_MAX_LEN_B       1024


#ifdef __cplusplus
extern "C" {
#endif


void Error_Handler(void);
void server_log(const char* format_string, ...);
void server_error(const char* format_string, ...);


#ifdef __cplusplus
}
#endif


#endif /* MAIN_H */

