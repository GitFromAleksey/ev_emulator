#include "cElectricityMeter.h"

namespace evse_logic
{

// ---------------------------------------------------------------------------
cElectricityMeter::cElectricityMeter(const char * name)
{
	TAG = name;
	LOG_DEBUG(TAG, "cElectricityMeter create");
}
// ---------------------------------------------------------------------------
cElectricityMeter::~cElectricityMeter()
{
	// TODO Auto-generated destructor stub
}
// ---------------------------------------------------------------------------
void cElectricityMeter::run(void *params)
{

}
// ---------------------------------------------------------------------------
void cElectricityMeter::SetGetTicksMsFunc(evse_ticks_ms_t (*getTicksMs)())
{
	LOG_DEBUG(TAG, "SetGetTicksMsFunc. Ticks = %d", getTicksMs());
}
// ---------------------------------------------------------------------------


} /* namespace evse_logic */
