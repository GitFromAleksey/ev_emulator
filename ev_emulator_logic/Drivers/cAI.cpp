#include <stddef.h>
#include "cAI.h"

namespace evse_logic
{

// ---------------------------------------------------------------------------
cADC::cADC(const char * name) :
	adcDataReady(NULL),
	adcStartCapture(NULL),
	adcGetCpData(NULL),
	adcGetPpData(NULL)
{
	TAG = name;
	LOG_DEBUG(TAG, "cADC create");
}
// ---------------------------------------------------------------------------
cADC::~cADC()
{
	// TODO Auto-generated destructor stub
}
// ---------------------------------------------------------------------------
void cADC::run(void *params)
{

}
// ---------------------------------------------------------------------------
void cADC::SetGetTicksMsFunc(evse_ticks_ms_t (*getTicksMs)())
{
	LOG_DEBUG(TAG, "SetGetTicksMsFunc. Ticks = %d", getTicksMs());
}
// ---------------------------------------------------------------------------
void cADC::SetAdcDataReadyCallback(bool (*adcDataReady)())
{	
	this->adcDataReady = adcDataReady;
}
// ---------------------------------------------------------------------------
void cADC::SetAdcStartCaptureCallback(void (*adcStartCapture)())
{	
	this->adcStartCapture = adcStartCapture;
}
// ---------------------------------------------------------------------------
void cADC::SetGetCpDataCallback(uint16_t (*adcGetCpData)(uint16_t * adc_data))
{	
	this->adcGetCpData = adcGetCpData;
}
// ---------------------------------------------------------------------------
void cADC::SetGetPpDataCallback(uint16_t (*adcGetPpData)(uint16_t * adc_data))
{	
	this->adcGetPpData = adcGetPpData;
}
// ---------------------------------------------------------------------------
void cADC::SetFiltrDepth(float depth) {}
// ---------------------------------------------------------------------------
void cADC::SetScale(float scale) {}
// ---------------------------------------------------------------------------
uint32_t cADC::GetRawValue()
{
	return 0;
}
// ---------------------------------------------------------------------------

} /* namespace evse_logic */
