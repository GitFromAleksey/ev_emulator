#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "cDebugInterface.h"

namespace evse_logic
{
// ---------------------------------------------------------------------------
cDebugInterface::cDebugInterface(const char * name) :
	SendMessageCallback(NULL)
{
	TAG = name;
	LOG_DEBUG(TAG, "cDebugInterface create");
}
// ---------------------------------------------------------------------------
cDebugInterface::~cDebugInterface () {}
// ---------------------------------------------------------------------------
void cDebugInterface::Update(t_view_update_data &data)
{
	if(SendMessageCallback == NULL)
		return;
	
	sprintf((char*)m_send_buf, "<TIME_MS:%u>", data.time_ms);
	SendMessageCallback(m_send_buf, sizeof(m_send_buf));
	
	sprintf((char*)m_send_buf, "<EV_STATE:%s>", data.ev_state);
	SendMessageCallback(m_send_buf, sizeof(m_send_buf));
	memset(m_send_buf, 0, SEND_BUF_SIZE);
	
	sprintf((char*)m_send_buf, "<CP_VAL:%u>", data.v_CP_ampl_value);
	SendMessageCallback(m_send_buf, sizeof(m_send_buf));
	
	sprintf((char*)m_send_buf, "<CP_DUTY:%u>", data.v_CP_duty_cycle);
	SendMessageCallback(m_send_buf, sizeof(m_send_buf));
	
	sprintf((char*)m_send_buf, "<PP_VAL:%u>", data.v_PP_value);
	SendMessageCallback(m_send_buf, sizeof(m_send_buf));

	m_send_buf[0] = '\n';
	SendMessageCallback(m_send_buf, 1);
	
}
// ---------------------------------------------------------------------------
void cDebugInterface::run(void *params)
{

}
// ---------------------------------------------------------------------------
void cDebugInterface::SetGetTicksMsFunc(evse_ticks_ms_t (*getTicksMs)())
{
	LOG_DEBUG(TAG, "SetGetTicksMsFunc. Ticks = %d", getTicksMs());
}
// ---------------------------------------------------------------------------
void cDebugInterface::SetSendMessageCallback(
											void (*sendMessageCallback)(uint8_t *msg, uint16_t len))
{
	SendMessageCallback = sendMessageCallback;
}
// ---------------------------------------------------------------------------

} /* namespace evse_logic */
