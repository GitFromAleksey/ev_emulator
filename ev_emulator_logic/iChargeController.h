#ifndef ICHARGECONTROLLER_H_
#define ICHARGECONTROLLER_H_

#include "Views/iView.h"
#include "States/iState.h"

namespace evse_logic
{

class iChargeController
{
public:
	virtual void AddView(iView &view) = 0;

protected:
	const char * TAG;
	iState *m_current_state;
};

} /* namespace ChargeController */

#endif /* ICHARGECONTROLLER_H_ */
