#ifndef _RX_LOGGER_H
#define _RX_LOGGER_H

#ifdef __cplusplus
    extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

typedef uint32_t (*timeLogStampGetter_t)(void);

void LOG_ENABLE(bool on);
void LOG_ADD_TIME_STAMP_GETTER(timeLogStampGetter_t timeLogStampGetter);

void LOG_ERROR(const char * tag, const char * _fmt, ...);
void LOG_WARNING(const char * tag, const char * _fmt, ...);
void LOG_INFO(const char * tag, const char * _fmt, ...);
void LOG_DEBUG(const char * tag, const char * _fmt, ...);
void LOG_VERBOSE(const char * tag, const char * _fmt, ...);

#ifdef __cplusplus
    }
#endif

#endif /* _RX_LOGGER_H */
