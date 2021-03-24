#ifndef MV_API_H
#define MV_API_H

#include <stdint.h>


/**
 *  32-bit result code from non-secure code. The top bit indicates
 *  an error. The remaining bits are an error code if the error bit
 *  is set, or something specific to the operation if not.
 */
enum MvStatus {
    MV_STATUS_OKAY                 = 0x0, //< Success
    MV_STATUS_PARAMETERFAULT       = 0x80000002, //< A pointer parameter pointed to unreadable/unwritable memory
};

struct MvTemporaryTestSubStruct {
    /// First member
    uint64_t a;
    /// Second member
    uint32_t b;
};

struct MvTemporaryTestStruct {
    /// First member
    uint8_t a;
    /// Second member
    struct MvTemporaryTestSubStruct *b;
    /// Third member
    uint32_t c;
};

struct MvTemporaryTestVersionedStruct {
    uint32_t version; //< version field; describes which other fields are valid
    union {
        struct {
            /// First member
            uint16_t a;
            /// Second member
            struct MvTemporaryTestStruct b;
        } v1;
    };
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  Does nothing, and returns Status::Okay.
 */
uint32_t mvNoOp(void);

/**
 *  Gets the current value of a free-running microsecond clock.  This
 *  clock starts from zero when the device OS starts, and counts up
 *  from then on.  It has no relation to (and may slew with respect
 *  to) wall time.
 *
 * Parameters:
 * @param[out]    ms              Pointer to receive result
 *
 * @retval MV_STATUS_PARAMETERFAULT ms is an illegal pointer
 */
uint32_t mvGetMicroseconds(uint64_t *ms);

/**
 *  Gets the current frequency of the CPU clock
 *
 * Parameters:
 * @param[out]    hz              Pointer to receive result
 *
 * @retval MV_STATUS_PARAMETERFAULT hz is an illegal pointer
 */
uint32_t mvGetSysClk(uint32_t *hz);

/**
 *  Gets the current frequency of the AHB bus
 *
 * Parameters:
 * @param[out]    hz              Pointer to receive result
 *
 * @retval MV_STATUS_PARAMETERFAULT hz is an illegal pointer
 */
uint32_t mvGetHClk(uint32_t *hz);

/**
 *  Gets the current frequency of the APB1 bus
 *
 * Parameters:
 * @param[out]    hz              Pointer to receive result
 *
 * @retval MV_STATUS_PARAMETERFAULT hz is an illegal pointer
 */
uint32_t mvGetPClk1(uint32_t *hz);

/**
 *  Gets the current frequency of the APB2 bus
 *
 * Parameters:
 * @param[out]    hz              Pointer to receive result
 *
 * @retval MV_STATUS_PARAMETERFAULT hz is an illegal pointer
 */
uint32_t mvGetPClk2(uint32_t *hz);

/**
 *  Gets the current time in seconds since the epoch
 *
 * Parameters:
 * @param[out]    sec             Pointer to receive result
 *
 * @retval MV_STATUS_PARAMETERFAULT sec is an illegal pointer
 */
uint32_t mvGetWallTime(uint32_t *sec);

/**
 *  Puts processor into stop mode sleep for 'sec' seconds
 *
 * Parameters:
 * @param         sec             Seconds to sleep
 *
 */
uint32_t mvSleep(uint32_t sec);

/**
 *  Sends a string to the server.
 *  This is not a real bit of networking API, and will be removed.
 *
 * Parameters:
 * @param[in]     s               Pointer to the utf8 string to send
 * @param         len             Length of the string pointed to by s
 *
 * @retval MV_STATUS_PARAMETERFAULT string is not entirely in non-secure memory
 */
uint32_t mvTemporaryServerLog(const uint8_t *s, uint32_t len);

/**
 *  Test structure parameters
 *
 * Parameters:
 * @param[in]     in              input structure
 *
 * @retval MV_STATUS_PARAMETERFAULT in is an illegal pointer
 */
uint32_t mvTemporaryStructTest(const struct MvTemporaryTestVersionedStruct *in);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // MV_API_H
