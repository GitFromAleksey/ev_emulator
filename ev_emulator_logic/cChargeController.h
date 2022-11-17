#ifndef CCHARGECONTROLLER_H_
#define CCHARGECONTROLLER_H_

#include "iChargeController.h"
#include "iThread.h"
//#include "Drivers/cDIO.h"
#include "Drivers/cDI.h"
#include "Drivers/cDO.h"
#include "Drivers/cAI.h"
#include "Drivers/cPWM.h"

namespace evse_logic
{

class cEvEmulator : public iChargeController, public iThread
{
public:

	cEvEmulator(const char * name);
	virtual ~cEvEmulator();

	virtual void AddView(iView &view);

	virtual void run(void *params);
	virtual void SetGetTicksMsFunc(evse_ticks_ms_t (*getTicksMs)());

	void ConnectLed(cDO *led_status);
	void ConnectS2Switch(cDO *v_s2_out_switch);
	void ConnectADC(cADC *adc);

private:
	uint16_t m_v_PP_value;      // значение сигнала PP, вольт
	uint16_t m_v_CP_ampl_value; // амплитуда сигнала CP, вольт

	cDO *m_led_status;
	cDO *m_v_s2_out_switch;
	cADC *m_adc;

	evse_ticks_ms_t (*GetTicksMs)();

	const uint8_t  FILTR_DEPTH  = 4;    // глубина фильтра
	const uint32_t LED_DELAY_MS = 500;  // период мигания светодиодом
	const uint32_t ADC_DELAY_MS = 1000; // период опроса АЦП

	void LedStatusDriver();
	void AdcCalculations();
	
	void V_PpCalc(uint16_t *adc_data_arr, uint16_t data_size);
	void V_CpCalc(uint16_t *adc_data_arr, uint16_t data_size);
	uint16_t FindMaxMinMiddle(uint16_t *p_max, uint16_t *p_middle, uint16_t *p_min, 
														uint16_t *adc_data_arr, uint16_t data_size);

	uint16_t AdcDataFiltr(uint16_t *data, uint16_t data_size);
	uint16_t AdcToVoltageCalc(uint16_t adc_data, uint32_t coef_fp);
};

} /* namespace ChargeController */

#endif /* CCHARGECONTROLLER_H_ */
