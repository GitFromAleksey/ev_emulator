#ifndef VIEWS_CLOCALCONTROL_H_
#define VIEWS_CLOCALCONTROL_H_

#include "iView.h"
#include "../iThread.h"

namespace evse_logic
{

class cLocalControl : public iView, public iThread
{
public:

	cLocalControl(const char * name);
	virtual ~cLocalControl();

	virtual void Update(t_view_update_data &data);

	virtual void run(void *params);
	virtual void SetGetTicksMsFunc(evse_ticks_ms_t (*getTicksMs)());
};

} /* namespace evse_logic */

#endif /* VIEWS_CLOCALCONTROL_H_ */
