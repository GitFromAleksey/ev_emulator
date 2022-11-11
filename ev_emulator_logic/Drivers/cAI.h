#ifndef DRIVERS_CAI_H_
#define DRIVERS_CAI_H_

#include <stdint.h>
#include "../iThread.h"

#include "../../Common/EvseLogger.h"

namespace evse_logic
{

class cAI : public iThread
{
public:
	cAI(const char * name);
	virtual ~cAI();

	virtual void run(void *params);
	virtual void SetGetTicksMsFunc(evse_ticks_ms_t (*getTicksMs)());

	void SetFiltrDepth(float depth);
	void SetScale(float scale);
	uint32_t GetRawValue();

protected:
	const char * TAG;
	float m_filtr_depth;
};

} /* namespace evse_logic */

#endif /* DRIVERS_CAI_H_ */
