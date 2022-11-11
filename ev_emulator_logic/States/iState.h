#ifndef STATES_ISTATE_H_
#define STATES_ISTATE_H_

#include "../iChargeController.h"

namespace evse_logic
{

class iChargeController;

class iState
{
	public:

	private:
		iChargeController *m_charge_controller;
};

} /* namespace evse_logic */

#endif /* STATES_ISTATE_H_ */
