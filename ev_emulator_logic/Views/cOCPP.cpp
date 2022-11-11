#include "cOCPP.h"

namespace evse_logic {

// ---------------------------------------------------------------------------
cOCPP::cOCPP(const char * name)
{
	TAG = name;
	LOG_DEBUG(TAG, "ocpp create.");
}
// ---------------------------------------------------------------------------
cOCPP::~cOCPP() {
	// TODO Auto-generated destructor stub
}
// ---------------------------------------------------------------------------
void cOCPP::Update(t_view_update_data &data)
{

}
// ---------------------------------------------------------------------------
void cOCPP::run(void *params)
{

}
// ---------------------------------------------------------------------------
void cOCPP::SetGetTicksMsFunc(evse_ticks_ms_t (*getTicksMs)())
{
	LOG_DEBUG(TAG, "SetGetTicksMsFunc. Ticks = %d", getTicksMs());
}
// ---------------------------------------------------------------------------

} /* namespace evse_logic */
