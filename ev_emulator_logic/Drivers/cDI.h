#ifndef DRIVERS_CDI_H_
#define DRIVERS_CDI_H_

#include "cDIO.h"
#include "../iThread.h"

namespace evse_logic
{

class cDI : public cDIO, public iThread
{
public:
	cDI(const char * name, bool inv);
	virtual ~cDI();

	virtual void run(void *params);
	virtual void SetGetTicksMsFunc(evse_ticks_ms_t (*getTicksMs)());
};

} /* namespace evse_logic */

#endif /* DRIVERS_CDI_H_ */
