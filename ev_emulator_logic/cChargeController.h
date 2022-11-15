#ifndef CCHARGECONTROLLER_H_
#define CCHARGECONTROLLER_H_

#include "iChargeController.h"
#include "iThread.h"
//#include "Drivers/cDIO.h"
#include "Drivers/cDI.h"
#include "Drivers/cDO.h"
#include "Drivers/cAI.h"
#include "Drivers/cPWM.h"

namespace evse_logic
{

class cChargeController : public iChargeController, public iThread
{
public:

	cChargeController(const char * name);
	virtual ~cChargeController();

	virtual void AddView(iView &view);

	virtual void run(void *params);
	virtual void SetGetTicksMsFunc(evse_ticks_ms_t (*getTicksMs)());

	void ConnectLed(cDO *led_status);
	void ConnectADC(cADC *adc);

private:

	cDO *m_led_status;
	cADC *m_adc;

	evse_ticks_ms_t (*GetTicksMs)();

	const uint32_t LED_DELAY_MS = 1000;
	const uint32_t ADC_DELAY_MS = 1000;

	void LedStatusDriver();
	void AdcDriver();
};

} /* namespace ChargeController */

#endif /* CCHARGECONTROLLER_H_ */
