#ifndef EVSE_MAIN_H_
#define EVSE_MAIN_H_

#include <stdint.h>

typedef uint32_t evse_ticks_ms_t;

typedef struct
{
	void (*uartSendMessage)(uint8_t *msg, uint16_t len);
	bool (*adcDataReady)();
	void (*adcStartCapture)();
	uint16_t (*adcGetCpData)(uint16_t * adc_data);
	uint16_t (*adcGetPpData)(uint16_t * adc_data);
	void (*vS2OutSwitch)(bool set);
	void (*ledStatusSwitch)(bool set);
	evse_ticks_ms_t (*getTicksMs)();
} evse_init_t;

void EvseInit(evse_init_t *evse_init);

void EvseRun(void *p);

#endif /* EVSE_MAIN_H_ */
