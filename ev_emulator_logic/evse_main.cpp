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

#include "iThread.h"

using namespace evse_logic;

std::list<iThread*> proc_list;
// ---------------------------------------------------------------------------
cEvEmulator *ev = NULL;
cLocalControl *local_control = NULL;
cOCPP *ocpp = NULL;
cDebugInterface *debug = NULL;

cDO *led_status = NULL;
cDO *v_s2_out_switch = NULL;
cADC *adc = NULL;


// ---------------------------------------------------------------------------
void EvseInit(evse_init_t *evse_init)
{
	LOG_DEBUG("__FILE__","EvseInit");
	
	ev = new cEvEmulator("EVSE");
	local_control = new cLocalControl("local control");
	ocpp = new cOCPP("ocpp");
	debug = new cDebugInterface("debug");

	led_status = new cDO("Led status", false);
	led_status->SetDriverSwitchCallback(evse_init->ledStatusSwitch);
	
	v_s2_out_switch = new cDO("V_S2_OUT", false);
	v_s2_out_switch->SetDriverSwitchCallback(evse_init->vS2OutSwitch);
	
	adc = new cADC("CP_LINE_CONTROL");
	adc->SetAdcDataReadyCallback(evse_init->adcDataReady);
	adc->SetAdcStartCaptureCallback(evse_init->adcStartCapture);
	adc->SetGetCpDataCallback(evse_init->adcGetCpData);
	adc->SetGetPpDataCallback(evse_init->adcGetPpData);

	debug->SetSendMessageCallback(evse_init->uartSendMessage);

	ev->AddView(*local_control);
	ev->AddView(*ocpp);
	ev->AddView(*debug);

	ev->ConnectLed(led_status);
	ev->ConnectS2Switch(v_s2_out_switch);
	ev->ConnectADC(adc);

	proc_list.push_back(ev);
	proc_list.push_back(local_control);
	proc_list.push_back(ocpp);
	proc_list.push_back(debug);

	proc_list.push_back(adc);


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
