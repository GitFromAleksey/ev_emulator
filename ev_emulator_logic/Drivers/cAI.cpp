#include "cAI.h"

namespace evse_logic
{

// ---------------------------------------------------------------------------
cAI::cAI(const char * name)
{
	TAG = name;
	LOG_DEBUG(TAG, "cAI create");
}
// ---------------------------------------------------------------------------
cAI::~cAI()
{
	// TODO Auto-generated destructor stub
}
// ---------------------------------------------------------------------------
void cAI::run(void *params)
{

}
// ---------------------------------------------------------------------------
void cAI::SetGetTicksMsFunc(evse_ticks_ms_t (*getTicksMs)())
{
	LOG_DEBUG(TAG, "SetGetTicksMsFunc. Ticks = %d", getTicksMs());
}
// ---------------------------------------------------------------------------
void cAI::SetFiltrDepth(float depth) {}
// ---------------------------------------------------------------------------
void cAI::SetScale(float scale) {}
// ---------------------------------------------------------------------------
uint32_t cAI::GetRawValue()
{
	return 0;
}
// ---------------------------------------------------------------------------

} /* namespace evse_logic */
