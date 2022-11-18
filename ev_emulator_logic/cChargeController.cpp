#include <stddef.h>
#include "cChargeController.h"

#include "../Common/EvseLogger.h"


#define ADC_RESOLUTION_PP    0x0FDC
#define MAX_INPUT_VOLTAGE_PP (3.4f) * 1000
#define COEF_PP    (MAX_INPUT_VOLTAGE_PP/ADC_RESOLUTION_PP)
#define COEF_FP_PP (uint32_t)(COEF_PP * 0xFFFF)

#define ADC_RESOLUTION_CP    0x0F8C
#define MAX_INPUT_VOLTAGE_CP (9.12f) * 1000
#define COEF_CP    (MAX_INPUT_VOLTAGE_CP/ADC_RESOLUTION_CP)
#define COEF_FP_CP (uint32_t)(COEF_CP * 0xFFFF)

namespace evse_logic {

// ---------------------------------------------------------------------------
cEvEmulator::cEvEmulator(const char * name) :
	m_EV_STATE(EV_STATE_NONE),
	m_v_PP_value(0),
	m_v_CP_ampl_value(0),
	m_v_CP_duty_cycle(0),
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
	m_views.push_back(&view);
}
// ---------------------------------------------------------------------------
void cEvEmulator::run(void *params)
{
	AvStateManager();
	LedStatusDriver();
	AdcCalculations();
	
	ViewsUpdate();
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
	
	#define DEFAULT_DELAY    1000u
	static uint32_t prev_time_ms = 0;
	uint16_t period = DEFAULT_DELAY;
	uint16_t delay = DEFAULT_DELAY>>1;
	uint32_t time_delta = GetTicksMs() - prev_time_ms;
	
	switch(m_EV_STATE)
	{
		case EV_STATE_NOT_CONNECT:
			delay = 10;
			break;
		case EV_STATE_CONNECT:
			delay = period;
			break;
		case EV_STATE_PWM:
			
			break;
		case EV_STATE_S2_ON:
			delay = DEFAULT_DELAY>>1;
			break;
		case EV_STATE_NONE:

			break;
		default:
			break;
	}
	
	if( time_delta > period)
	{
		prev_time_ms = GetTicksMs();
		m_led_status->SwitchOff(); // SetState(true); // LedStatusSwitch(true);

	}
	else if( time_delta > delay)
	{
		m_led_status->SwitchOn(); // SetState(false); // LedStatusSwitch(false);
	}
}
// ---------------------------------------------------------------------------
void cEvEmulator::AdcCalculations()
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
	
	adc_data_size = m_adc->adcGetPpData(&p_adc_data_arr);
	V_PpCalc(p_adc_data_arr, adc_data_size);

	adc_data_size = m_adc->adcGetCpData(&p_adc_data_arr);
	V_CpCalc(p_adc_data_arr, adc_data_size);
	
	LOG_DEBUG(TAG, "PP: %u,V; CP: %u,V; CP duty: %u,%%", 
									m_v_PP_value, m_v_CP_ampl_value, m_v_CP_duty_cycle);

	m_adc->adcStartCapture();
}
// ---------------------------------------------------------------------------
void cEvEmulator::V_PpCalc(uint16_t *adc_data_arr, uint16_t data_size)
{
	uint16_t temp = AdcDataFiltr(adc_data_arr, data_size);

	temp = AdcToVoltageCalc(temp, COEF_FP_PP);
	
	m_v_PP_value = temp;
}
// ---------------------------------------------------------------------------
void cEvEmulator::V_CpCalc(uint16_t *adc_data_arr, uint16_t data_size)
{
	uint16_t temp = 0;
	uint16_t max = 0;
	uint16_t min = 0;
	uint16_t middle = 0;
	
	temp = FindMaxMinMiddle(&max, &middle, &min, adc_data_arr, data_size);
	m_v_CP_ampl_value = AdcToVoltageCalc(max, COEF_FP_CP);
	m_v_CP_duty_cycle = DutyCyclyCalc(adc_data_arr, data_size, middle);
}
// ---------------------------------------------------------------------------
uint16_t cEvEmulator::FindMaxMinMiddle(uint16_t *p_max, uint16_t *p_middle, uint16_t *p_min, 
																	uint16_t *adc_data_arr, uint16_t data_size)
{
	uint16_t result = 0;
	uint16_t max = 0;
	int32_t max_accum = 0;
	uint16_t min = 0;
	int32_t min_accum = 0;
	
	for(uint16_t i = 0; i < data_size; ++i)
	{
		if(max < adc_data_arr[i])
		{
			max_accum -= max_accum>>2;
			max_accum += adc_data_arr[i];
			max = max_accum>>2;
		}
		if(min > adc_data_arr[i])
		{
			min_accum -= min_accum>>2;
			min_accum += adc_data_arr[i];
			min = min_accum>>2;			
		}
	}
	
	*p_max    = max;
	*p_middle = (max - min)>>1;
	*p_min    = min;
	
	return result;
}
// ---------------------------------------------------------------------------
uint8_t cEvEmulator::DutyCyclyCalc(uint16_t *adc_data_arr, uint16_t data_size, uint16_t middle)
{
	uint8_t result = 0;
	uint16_t hi_counter = 0;
	int32_t hi_counter_accum = 0;
	uint16_t lo_counter = 0;
	int32_t lo_counter_accum = 0;
	uint8_t shift = 1;
	
	bool prev_state = (adc_data_arr[0] > middle)?(true):(false);
	bool cur_state = prev_state;
	for(uint16_t i = 1; i < data_size; ++i)
	{
		prev_state = cur_state;
		cur_state = (adc_data_arr[i] > middle);
		if( (prev_state == false) && (cur_state == true))
		{
			// восходящий фронт
			hi_counter_accum -= hi_counter_accum>>shift;
			hi_counter_accum += hi_counter;
			hi_counter = 0;
		}
		else if( (prev_state == true) && (cur_state == false))
		{
			// низходящий фронт
			lo_counter_accum -= lo_counter_accum>>shift;
			lo_counter_accum += lo_counter;
			lo_counter = 0;
		}
		
		if(cur_state)
		{
			++hi_counter;
		}
		else
		{
			++lo_counter;
		}
	}
	hi_counter = hi_counter_accum>>shift;
	lo_counter = lo_counter_accum>>shift;
	
	result = ((hi_counter+lo_counter) == 0)?(0):((hi_counter*100)/(hi_counter+lo_counter));
	
	return result;
}
// ---------------------------------------------------------------------------
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
uint16_t cEvEmulator::AdcToVoltageCalc(uint16_t adc_data, uint32_t coef_fp)
{
	uint16_t result = 0;
	uint32_t temp = adc_data;

	temp = coef_fp * temp; // COEF_FP_PP * temp;
	temp = temp>>16;
	result = temp;
	
	return result;
}
// ---------------------------------------------------------------------------
void cEvEmulator::AvStateManager()
{
	static t_ev_state ev_state = m_EV_STATE;
	
	switch(m_EV_STATE)
	{
		case EV_STATE_NOT_CONNECT:
			m_v_s2_out_switch->SwitchOff();
			m_EV_STATE = (AvIsConnect())?(EV_STATE_CONNECT):(EV_STATE_NOT_CONNECT);
			break;
		case EV_STATE_CONNECT:
			m_v_s2_out_switch->SwitchOff();
			m_EV_STATE = (AvIsConnect())?(EV_STATE_CONNECT):(EV_STATE_NOT_CONNECT);
			if(m_v_CP_duty_cycle > 5)
				m_EV_STATE = EV_STATE_PWM;
			break;
		case EV_STATE_PWM:
			if(!AvIsConnect()) 
				m_EV_STATE = (EV_STATE_NOT_CONNECT);
			
			m_v_s2_out_switch->SwitchOn();
			m_EV_STATE = EV_STATE_S2_ON;
			break;
		case EV_STATE_S2_ON:
			if(!AvIsConnect()) 
				m_EV_STATE = (EV_STATE_NOT_CONNECT);
			if(m_v_CP_duty_cycle == 0)
				m_EV_STATE = (EV_STATE_NONE);
			break;
		case EV_STATE_NONE:
			m_EV_STATE = (AvIsConnect())?(EV_STATE_CONNECT):(EV_STATE_NOT_CONNECT);
			break;
		default:
			break;
	}
	
	if(ev_state != m_EV_STATE)
	{
		ev_state = m_EV_STATE;
		ViewsUpdate();
	}
}
// ---------------------------------------------------------------------------
bool cEvEmulator::AvIsConnect()
{
	uint16_t delta = 200;
	bool result = false;
	
	if( m_v_PP_value < (3156 + delta) )
	{
		if( m_v_PP_value > (3156 - delta) )
		{
			result = false;
		}
		if( m_v_PP_value < (1365 + delta) )
		{
			if( m_v_PP_value > (1365 - delta) )
			{
				result = true;
			}
		}
	}
	return result;
}
// ---------------------------------------------------------------------------
void cEvEmulator::ViewsUpdate()
{
	static uint32_t prev_time_ms = 0;
	uint32_t time_delta = GetTicksMs() - prev_time_ms;

	if(time_delta < 1000)
		return;
	prev_time_ms = GetTicksMs();
	
	t_view_update_data data;

	switch(m_EV_STATE)
	{
		case EV_STATE_NOT_CONNECT:
			data.ev_state = "NOT_CONNECT"; // "EV_STATE_NOT_CONNECT";
			break;
		case EV_STATE_CONNECT:
			data.ev_state = "EV_STATE_CONNECT";
			break;
		case EV_STATE_PWM:
			data.ev_state = "EV_STATE_PWM";
			break;
		case EV_STATE_S2_ON:
			data.ev_state = "EV_STATE_S2_ON";
			break;
		case EV_STATE_NONE:
			data.ev_state = "EV_STATE_NONE";
			break;
		default:
			break;
	}
	
	data.v_PP_value = m_v_PP_value;
	data.v_CP_ampl_value = m_v_CP_ampl_value;
	data.v_CP_duty_cycle = m_v_CP_duty_cycle;
	
	data.time_ms = GetTicksMs();
	
	for(auto it = m_views.begin(); it != m_views.end(); ++it)
	{
		dynamic_cast<iView*>(*it)->Update(data);
	}
}
// ---------------------------------------------------------------------------

} /* namespace ChargeController */
