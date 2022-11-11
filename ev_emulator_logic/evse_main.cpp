#include <stddef.h>
#include <list>
#include "evse_main.h"

#include "../Common/EvseLogger.h"

#include "cChargeController.h"
#include "Views/cDebugInterface.h"
#include "Views/cLocalControl.h"
#include "Views/cOCPP.h"

#include "Drivers/cDIO.h"
#include "Drivers/cDI.h"
#include "Drivers/cDO.h"
#include "Drivers/cAI.h"
#include "Drivers/cPWM.h"
#include "Drivers/cElectricityMeter.h"

#include "iThread.h"

using namespace evse_logic;

std::list<iThread*> proc_list;
// ---------------------------------------------------------------------------
cChargeController *evse = NULL;
cLocalControl *local_control = NULL;
cOCPP *ocpp = NULL;
cDebugInterface *debug = NULL;

cDO *vent_switch = NULL;
cDO *contactor_switch = NULL;
cDI *contactor_feedback = NULL;
cDI *emergency_stop_button = NULL;
cDI *leakage_current = NULL;
cAI *pp_proximity_plug = NULL;
cDO *evse_lock_signal = NULL;
cDI *evse_lock_signal_feedback = NULL;
cPWM *pwm = NULL;
cAI *cp_line_control = NULL;

cElectricityMeter *em = NULL;
//struct SetGetTicksMsFunc
//{
//};

// ---------------------------------------------------------------------------
void EvseInit(evse_init_t *evse_init)
{
	evse = new cChargeController("EVSE");
	local_control = new cLocalControl("local control");
	ocpp = new cOCPP("ocpp");
	debug = new cDebugInterface("debug");

	vent_switch = new cDO("VENT_SWITCH", false);
	contactor_switch = new cDO("CONTACTOR_SWITCH", false);
	contactor_feedback = new cDI("CONTACTOR_FEEDBACK", false);
	emergency_stop_button = new cDI("STOP_BUTTON", false);
	leakage_current = new cDI("LEAKAGE_CURRENT", false);
	pp_proximity_plug = new cAI("PP_PRIXIMITY_PLUG");
	evse_lock_signal = new cDO("LOCK_SIGNAL", false);
	evse_lock_signal_feedback = new cDI("LOCK_SIGNAL_FEEDBACK", false);
	pwm = new cPWM("PWM");
	cp_line_control = new cAI("CP_LINE_CONTROL");

	em = new cElectricityMeter("ElectricityMeter");


	evse->AddView(*local_control);
	evse->AddView(*ocpp);
	evse->AddView(*debug);

	evse->ConnectVent(vent_switch);
	evse->ConnectContactorSwitch(contactor_switch);
	evse->ConnectContactorFeedBack(contactor_feedback);
	evse->ConnectEmergencyStopButton(emergency_stop_button);
	evse->ConnectLeakageCurrentInput(leakage_current);
	evse->ConnectPPinput(pp_proximity_plug);
	evse->ConnectLockSignal(evse_lock_signal);
	evse->ConnectLockFeedback(evse_lock_signal_feedback);

	evse->ConnectPWM(pwm);
	evse->ConnectCP(cp_line_control);

	proc_list.push_back(evse);
	proc_list.push_back(local_control);
	proc_list.push_back(ocpp);
	proc_list.push_back(debug);

	proc_list.push_back(vent_switch);
	proc_list.push_back(contactor_switch);
	proc_list.push_back(contactor_feedback);
	proc_list.push_back(emergency_stop_button);
	proc_list.push_back(leakage_current);
	proc_list.push_back(pp_proximity_plug);
	proc_list.push_back(evse_lock_signal);
	proc_list.push_back(evse_lock_signal_feedback);
	proc_list.push_back(pwm);
	proc_list.push_back(cp_line_control);

	proc_list.push_back(em);

	for(auto it = proc_list.begin(); it != proc_list.end(); ++it)
	{
		dynamic_cast<iThread*>(*it)->SetGetTicksMsFunc(evse_init->getTicksMs);
	}
}
// ---------------------------------------------------------------------------
void EvseRun(void *p)
{
	for(auto it = proc_list.begin(); it != proc_list.end(); ++it)
	{
		dynamic_cast<iThread*>(*it)->run(NULL);
	}
}
// ---------------------------------------------------------------------------
