#include "cDIO.h"

namespace evse_logic
{

// ---------------------------------------------------------------------------
cDIO::cDIO(const char * name, bool inv)
{
	TAG = name;
	SetInversion(inv);
	LOG_DEBUG(TAG, "cDIO create. Iverse: %s", (inv)?("on"):("off"));
}
// ---------------------------------------------------------------------------
cDIO::~cDIO() {}
// ---------------------------------------------------------------------------
bool cDIO::IsOn() { return false; }
// ---------------------------------------------------------------------------
bool cDIO::IsInverse() { return m_inversion; }
// ---------------------------------------------------------------------------
void cDIO::SetInversion(bool inv) { m_inversion = inv; }
// ---------------------------------------------------------------------------

} /* namespace evse_logic */
