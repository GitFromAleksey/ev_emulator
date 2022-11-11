#ifndef DRIVERS_CDIO_H_
#define DRIVERS_CDIO_H_

#include "../../Common/EvseLogger.h"

namespace evse_logic
{

class cDIO
{
public:
	cDIO(const char * name, bool inv);
	virtual ~cDIO();

	bool IsOn();
	bool IsInverse();
	void SetInversion(bool inv);

protected:
	const char * TAG;
	bool m_inversion;
};

} /* namespace evse_logic */

#endif /* DRIVERS_CDIO_H_ */
