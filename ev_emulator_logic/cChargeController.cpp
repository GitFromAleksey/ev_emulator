#include <stddef.h>
#include "cChargeController.h"

#include "../Common/EvseLogger.h"


namespace evse_logic {

// ---------------------------------------------------------------------------
cChargeController::cChargeController(const char * name) :
	m_vent_switch(NULL),
	m_contactor_switch(NULL),
	m_contactor_feedback(NULL),
	m_emergency_stop_button(NULL),
	m_leakage_current(NULL),

	m_pp_proximity_plug(NULL),
	m_evse_lock_signal(NULL),
	m_evse_lock_signal_feedback(NULL),

	m_pwm(NULL),
	m_cp_line_control(NULL)
{
	TAG = name;
	LOG_DEBUG(TAG, "create charge controller.");
}
// ---------------------------------------------------------------------------
cChargeController::~cChargeController() {
	// TODO Auto-generated destructor stub
}
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
// ---------------------------------------------------------------------------
void cChargeController::ConnectVent( cDO *vent_switch)
{ m_vent_switch = vent_switch; }
// ---------------------------------------------------------------------------
void cChargeController::ConnectContactorSwitch(cDO *contactor_switch)
{ m_contactor_switch = contactor_switch; }
// ---------------------------------------------------------------------------
void cChargeController::ConnectContactorFeedBack(cDI *contactor_feedback)
{ m_contactor_feedback = contactor_feedback; }
// ---------------------------------------------------------------------------
void cChargeController::ConnectEmergencyStopButton(cDI *emergency_stop_button)
{ m_emergency_stop_button = emergency_stop_button; }
// ---------------------------------------------------------------------------
void cChargeController::ConnectLeakageCurrentInput(cDI *leakage_current)
{ m_leakage_current = leakage_current; }
// ---------------------------------------------------------------------------
void cChargeController::ConnectPPinput(cAI *pp_proximity_plug)
{ m_pp_proximity_plug = pp_proximity_plug; }
// ---------------------------------------------------------------------------
void cChargeController::ConnectLockSignal(cDO *evse_lock_signal)
{ m_evse_lock_signal = evse_lock_signal; }
// ---------------------------------------------------------------------------
void cChargeController::ConnectLockFeedback(cDI *evse_lock_signal_feedback)
{ m_evse_lock_signal_feedback = evse_lock_signal_feedback; }
// ---------------------------------------------------------------------------
void cChargeController::ConnectPWM(cPWM *pwm)
{ m_pwm = pwm; }
// ---------------------------------------------------------------------------
void cChargeController::ConnectCP(cAI *cp_line_control)
{ m_cp_line_control = cp_line_control; }
// ---------------------------------------------------------------------------

} /* namespace ChargeController */
