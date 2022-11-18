#ifndef VIEWS_CDEBUGINTERFACE_H_
#define VIEWS_CDEBUGINTERFACE_H_

#include "iView.h"
#include "../iThread.h"

namespace evse_logic
{

class cDebugInterface : public iView, public iThread
{
  public:
    cDebugInterface ();
    cDebugInterface(const char * name);
    virtual ~cDebugInterface ();

    virtual void Update(t_view_update_data &data);

		virtual void run(void *params);
		virtual void SetGetTicksMsFunc(evse_ticks_ms_t (*getTicksMs)());
	
		void SetSendMessageCallback(void (*sendMessageCallback)(uint8_t *msg, uint16_t len));
	
	private:
		static const uint16_t SEND_BUF_SIZE = 30;
		uint8_t m_send_buf[SEND_BUF_SIZE];
		void (*SendMessageCallback)(uint8_t *msg, uint16_t len);
	
};

} /* namespace evse_logic */

#endif /* VIEWS_CDEBUGINTERFACE_H_ */
