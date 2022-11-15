#include <stddef.h>
#include "cDO.h"

namespace evse_logic
{

// ---------------------------------------------------------------------------
cDO::cDO(const char * name, bool inv) :
		cDIO(name, inv),
		SwitchCallback(NULL)
{
	LOG_DEBUG(TAG, "cDO create");
	SetState(true);
}
// ---------------------------------------------------------------------------
cDO::~cDO() {}
// ---------------------------------------------------------------------------
void cDO::run(void *params)
{

}
// ---------------------------------------------------------------------------
void cDO::SetGetTicksMsFunc(evse_ticks_ms_t (*getTicksMs)())
{
	LOG_DEBUG(TAG, "SetGetTicksMsFunc. Ticks = %d", getTicksMs());
}
// ---------------------------------------------------------------------------
void cDO::SetDriverSwitchCallback(void (*switchCallback)(bool set))
{ SwitchCallback = switchCallback; }
// ---------------------------------------------------------------------------
void cDO::SetState(bool state) 
{
	if(SwitchCallback == NULL)
	{
		LOG_DEBUG(TAG, "SwitchCallback == NULL");
		return;
	}
	SwitchCallback(state);
}
// ---------------------------------------------------------------------------
void cDO::SwitchOn() { SetState(true); }
// ---------------------------------------------------------------------------
void cDO::SwitchOff() { SetState(false); }
// ---------------------------------------------------------------------------
void cDO::Toggle() {}
// ---------------------------------------------------------------------------

} /* namespace evse_logic */
