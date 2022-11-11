#ifndef DRIVERS_CPWM_H_
#define DRIVERS_CPWM_H_

#include <stdint.h>

#include "../../Common/EvseLogger.h"
#include "../iThread.h"

namespace evse_logic
{

class cPWM : public iThread
{
public:
	cPWM(const char * name);
	virtual ~cPWM();

	virtual void run(void *params);
	virtual void SetGetTicksMsFunc(evse_ticks_ms_t (*getTicksMs)());

	void SetFequency(uint32_t freq);
	uint32_t GetFequency();
	void SwitchOn();
	void SwitchOff();
	bool IsSwitchOn();
	void SetPwmDuty(uint8_t duty);
	uint8_t GetPwmDuty();

protected:
	const char * TAG;
};

} /* namespace evse_logic */

#endif /* DRIVERS_CPWM_H_ */
