#ifndef DRIVERS_CELECTRICITYMETER_H_
#define DRIVERS_CELECTRICITYMETER_H_

#include <stdint.h>

#include "../../Common/EvseLogger.h"
#include "../iThread.h"

namespace evse_logic
{

class cElectricityMeter : public iThread
{
public:
	cElectricityMeter(const char * name);
	virtual ~cElectricityMeter();

	virtual void run(void *params);
	virtual void SetGetTicksMsFunc(evse_ticks_ms_t (*getTicksMs)());

private:
	const char * TAG;
};

} /* namespace evse_logic */

#endif /* DRIVERS_CELECTRICITYMETER_H_ */
