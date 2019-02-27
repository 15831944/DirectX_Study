#include "JEvent.h"
#include "JEventList.h"
namespace UI
{
	bool JEvent::Frame()
	{
		if(bEventPlay)
			EventPlay(*this);
		return true;
	}
	JEvent* JEvent::ShowPanel(UI::JPanel& desk)
	{
		JEvent* pEvent = new JEvent;
		/* 쓸 Data만 저장 */
		pEvent->pDesk = &desk;
		/* 함수포인터 바인드 */
		pEvent->EventPlay = UI::SHOW_PANEL;
		return pEvent;
	}
	JEvent* JEvent::ShowPanelScl(UI::JPanel& desk)
	{
		JEvent* pEvent = new JEvent;
		/* 쓸 Data만 저장 */
		pEvent->pDesk = &desk;
		/* 함수포인터 바인드 */
		pEvent->EventPlay = UI::SHOW_PANEL_SCL;
		return pEvent;
	}
	JEvent::JEvent()
	{
	}


	JEvent::~JEvent()
	{
	}
}