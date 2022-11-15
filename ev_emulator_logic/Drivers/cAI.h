#ifndef DRIVERS_CAI_H_
#define DRIVERS_CAI_H_

#include <stdint.h>
#include "../iThread.h"

#include "../../Common/EvseLogger.h"

namespace evse_logic
{

class cADC : public iThread
{
public:

	bool (*adcDataReady)();
	void (*adcStartCapture)();
	uint16_t (*adcGetCpData)(uint16_t * adc_data);
	uint16_t (*adcGetPpData)(uint16_t * adc_data);

	cADC(const char * name);
	virtual ~cADC();

	virtual void run(void *params);
	virtual void SetGetTicksMsFunc(evse_ticks_ms_t (*getTicksMs)());

	void SetAdcDataReadyCallback(bool (*adcDataReady)());
	void SetAdcStartCaptureCallback(void (*adcStartCapture)());
	void SetGetCpDataCallback(uint16_t (*adcGetCpData)(uint16_t * adc_data));
	void SetGetPpDataCallback(uint16_t (*adcGetPpData)(uint16_t * adc_data));

	void SetFiltrDepth(float depth);
	void SetScale(float scale);
	uint32_t GetRawValue();

protected:
	const char * TAG;
	float m_filtr_depth;



};

} /* namespace evse_logic */

#endif /* DRIVERS_CAI_H_ */
