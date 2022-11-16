#include <stddef.h>
#include "cChargeController.h"

#include "../Common/EvseLogger.h"


namespace evse_logic {

// ---------------------------------------------------------------------------
cEvEmulator::cEvEmulator(const char * name) :
	m_led_status(NULL),
	m_v_s2_out_switch(NULL),
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
void cEvEmulator::ConnectS2Switch(cDO *v_s2_out_switch)
{ m_v_s2_out_switch = v_s2_out_switch; }
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
	uint16_t *p_adc_data_arr = NULL;
	uint16_t adc_data_size = 0;

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
//	LOG_DEBUG(TAG, "AdcDriver!");
	
	adc_data_size = m_adc->adcGetCpData(&p_adc_data_arr);
	adc_data_size = AdcDataFiltr(p_adc_data_arr, adc_data_size);
	LOG_DEBUG( TAG, "PP raw value: 0x%X", AdcToVoltageCalc(adc_data_size) );
	LOG_DEBUG( TAG, "PP value: %u, V", AdcToVoltageCalc(adc_data_size) );
	//LOG_DEBUG( TAG, "PP value: %u", AdcToVoltageCalc(p_adc_data_arr[10]) );
	
//	if(m_adc->adcDataReady)
	m_adc->adcStartCapture();
}
// ---------------------------------------------------------------------------
#define FILTR_DEPTH    4u
uint16_t cEvEmulator::AdcDataFiltr(uint16_t *data, uint16_t data_size)
{
	int32_t data_accum = 0;
	
	if(data_size > 0)
		data_accum = data[0];
	else
		return 0;
	
	for(int i = 1; i < data_size; ++i)
	{
		data_accum -= data_accum>>FILTR_DEPTH;
		data_accum += data[i];
	}
	return (uint16_t)(data_accum>>FILTR_DEPTH);
}
// ---------------------------------------------------------------------------
#define ADC_RESOLUTION    0x0FDC
#define MAX_INPUT_VOLTAGE (3.33f) * 1000
#define COEF    (MAX_INPUT_VOLTAGE/ADC_RESOLUTION)
#define COEF_FP (uint32_t)(COEF * 0xFFFF)

uint16_t cEvEmulator::AdcToVoltageCalc(uint16_t adc_data)
{
	uint16_t result = 0;
	uint32_t temp = adc_data;

	temp = COEF_FP * temp;
	temp = temp>>16;
	result = temp;
	
	return result;
}
// ---------------------------------------------------------------------------

} /* namespace ChargeController */
