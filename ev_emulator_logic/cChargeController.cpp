#include <stddef.h>
#include "cChargeController.h"

#include "../Common/EvseLogger.h"


namespace evse_logic {

// ---------------------------------------------------------------------------
cChargeController::cChargeController(const char * name) :
	m_led_status(NULL),
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
	LedStatusDriver();
}
// ---------------------------------------------------------------------------
void cChargeController::SetGetTicksMsFunc(evse_ticks_ms_t (*getTicksMs)())
{
	GetTicksMs = getTicksMs;
	LOG_DEBUG(TAG, "SetGetTicksMsFunc. Ticks = %d", GetTicksMs());
}
// ---------------------------------------------------------------------------
void cChargeController::ConnectLed(cDO *led_status)
{ m_led_status = led_status; }
// ---------------------------------------------------------------------------
void cChargeController::ConnectCP(cADC *cp_line_control)
{ m_cp_line_control = cp_line_control; }
// ---------------------------------------------------------------------------
// private
// ---------------------------------------------------------------------------
void cChargeController::LedStatusDriver()
{
	static uint32_t ticks = 0;
	static bool led_state = false;
	
	if(m_led_status == NULL)
	{
		LOG_ERROR(TAG, "m_led_status == NULL");
		return;
	}
	
	if(GetTicksMs == NULL)
	{
		LOG_ERROR(TAG, "GetTicksMs == NULL");
		return;
	}
	
	if( (GetTicksMs() - ticks) >= led_delay_ms )
	{
		ticks = GetTicksMs();
		m_led_status->SetState(led_state);
		led_state = !led_state;
	}
}
// ---------------------------------------------------------------------------

} /* namespace ChargeController */
