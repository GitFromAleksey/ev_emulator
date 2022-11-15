#include <stddef.h>
#include "cAI.h"

namespace evse_logic
{

// ---------------------------------------------------------------------------
cADC::cADC(const char * name)
{
	TAG = name;
	LOG_DEBUG(TAG, "cADC create");
	
	adcDataReady    = NULL;
	adcStartCapture = NULL;
	adcGetCpData       = NULL;
	adcGetPpData       = NULL;
}
// ---------------------------------------------------------------------------
cADC::~cADC()
{
	// TODO Auto-generated destructor stub
}
// ---------------------------------------------------------------------------
void cADC::run(void *params)
{

}
// ---------------------------------------------------------------------------
void cADC::SetGetTicksMsFunc(evse_ticks_ms_t (*getTicksMs)())
{
	LOG_DEBUG(TAG, "SetGetTicksMsFunc. Ticks = %d", getTicksMs());
}
// ---------------------------------------------------------------------------
void cADC::SetFiltrDepth(float depth) {}
// ---------------------------------------------------------------------------
void cADC::SetScale(float scale) {}
// ---------------------------------------------------------------------------
uint32_t cADC::GetRawValue()
{
	return 0;
}
// ---------------------------------------------------------------------------

} /* namespace evse_logic */
