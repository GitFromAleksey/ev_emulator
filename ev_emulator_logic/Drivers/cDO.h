#ifndef DRIVERS_CDO_H_
#define DRIVERS_CDO_H_

#include "cDIO.h"
#include "../iThread.h"

namespace evse_logic
{

class cDO : public cDIO, public iThread
{
public:
	cDO(const char * name, bool inv);
	virtual ~cDO();

	virtual void run(void *params);
	virtual void SetGetTicksMsFunc(evse_ticks_ms_t (*getTicksMs)());

	void SetDriverSwitchCallback(void (*switchCallback)(bool set));
	void SetState(bool state);
	void SwitchOn();
	void SwitchOff();
	void Toggle();

private:
	
	void (*SwitchCallback)(bool set);

};

} /* namespace evse_logic */

#endif /* DRIVERS_CDO_H_ */
