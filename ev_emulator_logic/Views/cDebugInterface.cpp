#include "cDebugInterface.h"

namespace evse_logic
{
// ---------------------------------------------------------------------------
cDebugInterface::cDebugInterface(const char * name)
{
	TAG = name;
	LOG_DEBUG(TAG, "cDebugInterface create");
}
// ---------------------------------------------------------------------------
cDebugInterface::~cDebugInterface () {}
// ---------------------------------------------------------------------------
void cDebugInterface::Update(t_view_update_data &data)
{

}
// ---------------------------------------------------------------------------
void cDebugInterface::run(void *params)
{

}
// ---------------------------------------------------------------------------
void cDebugInterface::SetGetTicksMsFunc(evse_ticks_ms_t (*getTicksMs)())
{
	LOG_DEBUG(TAG, "SetGetTicksMsFunc. Ticks = %d", getTicksMs());
}
// ---------------------------------------------------------------------------

} /* namespace evse_logic */
