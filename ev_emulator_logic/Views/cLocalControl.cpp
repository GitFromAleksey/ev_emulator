#include "cLocalControl.h"

namespace evse_logic {

// ---------------------------------------------------------------------------
cLocalControl::cLocalControl(const char * name)
{
	TAG = name;
	LOG_DEBUG(TAG, "cLocalControl create");
}
// ---------------------------------------------------------------------------
cLocalControl::~cLocalControl() {
	// TODO Auto-generated destructor stub
}
// ---------------------------------------------------------------------------
void cLocalControl::Update(t_view_update_data &data)
{

}
// ---------------------------------------------------------------------------
void cLocalControl::run(void *params)
{

}
// ---------------------------------------------------------------------------
void cLocalControl::SetGetTicksMsFunc(evse_ticks_ms_t (*getTicksMs)())
{
	LOG_DEBUG(TAG, "SetGetTicksMsFunc. Ticks = %d", getTicksMs());
}
// ---------------------------------------------------------------------------

} /* namespace evse_logic */


