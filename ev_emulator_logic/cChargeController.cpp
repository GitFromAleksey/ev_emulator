#include <stddef.h>
#include "cChargeController.h"

#include "../Common/EvseLogger.h"


namespace evse_logic {

// ---------------------------------------------------------------------------
cEvEmulator::cEvEmulator(const char * name) :
	m_led_status(NULL),
	m_adc(NULL)
{
	TAG = name;
	LOG_DEBUG(TAG, "create charge controller.");
}
// ---------------------------------------------------------------------------
cEvEmulator::~cEvEmulator() {}
// ---------------------------------------------------------------------------
void cEvEmulator::AddView(iView &view)
{
	LOG_DEBUG(TAG, "Add view.");
}
// ---------------------------------------------------------------------------
void cEvEmulator::run(void *params)
{
	LedStatusDriver();
	AdcDriver();
}
// ---------------------------------------------------------------------------
void cEvEmulator::SetGetTicksMsFunc(evse_ticks_ms_t (*getTicksMs)())
{
	GetTicksMs = getTicksMs;
	LOG_DEBUG(TAG, "SetGetTicksMsFunc. Ticks = %d", GetTicksMs());
}
// ---------------------------------------------------------------------------
void cEvEmulator::ConnectLed(cDO *led_status)
{ m_led_status = led_status; }
// ---------------------------------------------------------------------------
void cEvEmulator::ConnectADC(cADC *adc)
{ m_adc = adc; }
// ---------------------------------------------------------------------------
// private
// ---------------------------------------------------------------------------
void cEvEmulator::LedStatusDriver()
{
	static uint32_t ticks = 0;
	static bool led_state = false;
	
	if(m_led_status == NULL)
	{
		LOG_ERROR(TAG, "m_led_status == NULL");
		return;
	}
	
	if(GetTicksMs == NULL)
	{
		LOG_ERROR(TAG, "GetTicksMs == NULL");
		return;
	}
	
	if( (GetTicksMs() - ticks) >= LED_DELAY_MS )
	{
		ticks = GetTicksMs();
		m_led_status->SetState(led_state);
		led_state = !led_state;
//		LOG_DEBUG(TAG, "led blink!");
	}
}
// ---------------------------------------------------------------------------
void cEvEmulator::AdcDriver()
{
	static uint32_t ticks = 0;

	if(GetTicksMs == NULL)
	{
		LOG_ERROR(TAG, "GetTicksMs == NULL");
		return;
	}
	
	if( (GetTicksMs() - ticks) < ADC_DELAY_MS )
		return;
	ticks = GetTicksMs();
	
	if(m_adc == NULL)
	{
		LOG_ERROR(TAG, "m_adc == NULL");
		return;
	}
	LOG_DEBUG(TAG, "AdcDriver!");
//	if(m_adc->adcDataReady)
		m_adc->adcStartCapture();
}
// ---------------------------------------------------------------------------

} /* namespace ChargeController */
