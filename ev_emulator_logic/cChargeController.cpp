#include <stddef.h>
#include "cChargeController.h"

#include "../Common/EvseLogger.h"


namespace evse_logic {

// ---------------------------------------------------------------------------
cChargeController::cChargeController(const char * name) :
	m_lad_status(NULL),
	m_cp_line_control(NULL)
{
	TAG = name;
	LOG_DEBUG(TAG, "create charge controller.");
}
// ---------------------------------------------------------------------------
cChargeController::~cChargeController() {}
// ---------------------------------------------------------------------------
void cChargeController::AddView(iView &view)
{
	LOG_DEBUG(TAG, "Add view.");
}
// ---------------------------------------------------------------------------
void cChargeController::run(void *params)
{

}
// ---------------------------------------------------------------------------
void cChargeController::SetGetTicksMsFunc(evse_ticks_ms_t (*getTicksMs)())
{
	GetTicksMs = getTicksMs;
	LOG_DEBUG(TAG, "SetGetTicksMsFunc. Ticks = %d", GetTicksMs());
}
// ---------------------------------------------------------------------------
void cChargeController::ConnectCP(cAI *cp_line_control)
{ m_cp_line_control = cp_line_control; }
// ---------------------------------------------------------------------------

} /* namespace ChargeController */
