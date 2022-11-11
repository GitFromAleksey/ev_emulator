#ifndef ITHREAD_H_
#define ITHREAD_H_

#include "evse_main.h"

namespace evse_logic
{

class iThread
{
public:
	virtual void run(void *params) = 0;
	virtual void SetGetTicksMsFunc(evse_ticks_ms_t (*getTicksMs)()) = 0;
};

} /* namespace evse_logic */

#endif /* ITHREAD_H_ */
