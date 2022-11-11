#ifndef VIEWS_COCPP_H_
#define VIEWS_COCPP_H_

#include "iView.h"
#include "../iThread.h"

namespace evse_logic
{

  class cOCPP : public iView, public iThread
  {
	public:

		cOCPP(const char * name);
		virtual ~cOCPP();

		virtual void Update(t_view_update_data &data);

		virtual void run(void *params);
		virtual void SetGetTicksMsFunc(evse_ticks_ms_t (*getTicksMs)());
  };

} /* namespace evse_logic */

#endif /* VIEWS_COCPP_H_ */
