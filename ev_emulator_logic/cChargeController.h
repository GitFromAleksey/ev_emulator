#ifndef CCHARGECONTROLLER_H_
#define CCHARGECONTROLLER_H_

#include "iChargeController.h"
#include "iThread.h"
//#include "Drivers/cDIO.h"
#include "Drivers/cDI.h"
#include "Drivers/cDO.h"
#include "Drivers/cAI.h"
#include "Drivers/cPWM.h"

namespace evse_logic
{

class cChargeController : public iChargeController, public iThread
{
public:

	cChargeController(const char * name);
	virtual ~cChargeController();

	virtual void AddView(iView &view);

	virtual void run(void *params);
	virtual void SetGetTicksMsFunc(evse_ticks_ms_t (*getTicksMs)());

	void ConnectVent( cDO *m_vent_switch);
	void ConnectContactorSwitch(cDO *m_contactor_switch);
	void ConnectContactorFeedBack(cDI *m_contactor_feedback);
	void ConnectEmergencyStopButton(cDI *m_emergency_stop_button);
	void ConnectLeakageCurrentInput(cDI *m_leakage_current);

	void ConnectPPinput(cAI *m_pp_proximity_plug);
	void ConnectLockSignal(cDO *m_evse_lock_signal);
	void ConnectLockFeedback(cDI *m_evse_lock_signal_feedback);

	void ConnectPWM(cPWM *m_pwm);
	void ConnectCP(cAI *m_cp_line_control);

private:
	cDO *m_vent_switch;
	cDO *m_contactor_switch;
	cDI *m_contactor_feedback;
	cDI *m_emergency_stop_button;
	cDI *m_leakage_current;

	cAI *m_pp_proximity_plug;
	cDO *m_evse_lock_signal;
	cDI *m_evse_lock_signal_feedback;

	cPWM *m_pwm;
	cAI *m_cp_line_control;

	evse_ticks_ms_t (*GetTicksMs)();
};

} /* namespace ChargeController */

#endif /* CCHARGECONTROLLER_H_ */
