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
cChargeController *evse = NULL;
cLocalControl *local_control = NULL;
cOCPP *ocpp = NULL;
cDebugInterface *debug = NULL;

cAI *cp_line_control = NULL;


// ---------------------------------------------------------------------------
void EvseInit(evse_init_t *evse_init)
{
	evse = new cChargeController("EVSE");
	local_control = new cLocalControl("local control");
	ocpp = new cOCPP("ocpp");
	debug = new cDebugInterface("debug");


	cp_line_control = new cAI("CP_LINE_CONTROL");


	evse->AddView(*local_control);
	evse->AddView(*ocpp);
	evse->AddView(*debug);

	evse->ConnectCP(cp_line_control);

	proc_list.push_back(evse);
	proc_list.push_back(local_control);
	proc_list.push_back(ocpp);
	proc_list.push_back(debug);

	proc_list.push_back(cp_line_control);


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
