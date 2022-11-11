#ifndef VIEWS_IVIEW_H_
#define VIEWS_IVIEW_H_

#include "../../Common/EvseLogger.h"

namespace evse_logic
{

typedef struct
{

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
