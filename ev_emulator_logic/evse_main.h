#ifndef EVSE_MAIN_H_
#define EVSE_MAIN_H_

#include <stdint.h>

typedef uint32_t evse_ticks_ms_t;

typedef struct
{
	evse_ticks_ms_t (*getTicksMs)();
} evse_init_t;

void EvseInit(evse_init_t *evse_init);

void EvseRun(void *p);

#endif /* EVSE_MAIN_H_ */
