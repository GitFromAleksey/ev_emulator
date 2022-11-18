#ifndef VIEWS_IVIEW_H_
#define VIEWS_IVIEW_H_

#include "../../Common/EvseLogger.h"

namespace evse_logic
{

typedef struct
{
	char * ev_state;
	uint16_t v_PP_value;      // значение сигнала PP, вольт
	uint16_t v_CP_ampl_value; // амплитуда сигнала CP, вольт
	uint8_t v_CP_duty_cycle; // скважность сигнала CP, вольт
} t_view_update_data;

class iView
{
public:
	virtual void Update(t_view_update_data &data) = 0;
protected:
	const char * TAG;
};

} /* namespace evse_logic */

#endif /* VIEWS_IVIEW_H_ */
