#include "cDI.h"

namespace evse_logic
{

// ---------------------------------------------------------------------------
cDI::cDI(const char * name, bool inv) :
		cDIO(name, inv)
{
	LOG_DEBUG(TAG, "cDI create");
}
// ---------------------------------------------------------------------------
cDI::~cDI() { }
// ---------------------------------------------------------------------------
void cDI::run(void *params)
{

}
// ---------------------------------------------------------------------------
void cDI::SetGetTicksMsFunc(evse_ticks_ms_t (*getTicksMs)())
{
	LOG_DEBUG(TAG, "SetGetTicksMsFunc. Ticks = %d", getTicksMs());
}
// ---------------------------------------------------------------------------


} /* namespace evse_logic */
