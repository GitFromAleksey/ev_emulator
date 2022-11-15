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

	void ConnectCP(cAI *m_cp_line_control);

private:

	cDO *m_lad_status;
	cAI *m_cp_line_control;

	evse_ticks_ms_t (*GetTicksMs)();
};

} /* namespace ChargeController */

#endif /* CCHARGECONTROLLER_H_ */
