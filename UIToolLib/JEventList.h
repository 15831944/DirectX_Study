#pragma once
#include "JEvent.h"
#include "Timer.h"
namespace UI
{
	/* ���� �̺�Ʈ�� JEvent���� ������ ��ü�� ������ ���ư� */
	static void SHOW_PANEL(UI::JEvent& pEvent)
	{
		pEvent.pDesk->m_bRender = !pEvent.pDesk->m_bRender;
		pEvent.bEventPlay = false;
	}

	static void SHOW_PANEL_SCL(UI::JEvent& pEvent)
	{
		D3DXVECTOR3 vCurScl = pEvent.pDesk->m_pCurTransform->m_vScl;
		/* ������ */
		if (pEvent.pDesk->m_bRender)
		{
			if( pEvent.pDesk->m_vScl.x >= 0.1f || 
				pEvent.pDesk->m_vScl.y >= 0.1f)
			{
				if (pEvent.pDesk->m_vScl.x >= 0.1f)
					pEvent.pDesk->m_vScl.x -= Timer::SPF * vCurScl.x;
				if( pEvent.pDesk->m_vScl.y >= 0.1f)
					pEvent.pDesk->m_vScl.y -= Timer::SPF * vCurScl.y;
			}
			else
			{
				pEvent.pDesk->m_vScl -= D3DXVECTOR3(0.1f, 0.1f, 0);
				pEvent.pDesk->m_bRender = false;
				pEvent.bEventPlay = false;
			}
		}
		/* ������ */
		else
		{
			if ( pEvent.pDesk->m_vScl.x <= vCurScl.x ||
				 pEvent.pDesk->m_vScl.y <= vCurScl.y)
			{
				/* �ʴ� 10�� */
				if (pEvent.pDesk->m_vScl.x < vCurScl.x)
					pEvent.pDesk->m_vScl.x += Timer::SPF * vCurScl.x;
				if (pEvent.pDesk->m_vScl.y < vCurScl.y)
					pEvent.pDesk->m_vScl.y += Timer::SPF * vCurScl.y;
			}
			else
			{
				pEvent.pDesk->m_vScl += D3DXVECTOR3(0.1f, 0.1f, 0);
				pEvent.pDesk->m_bRender = true;
				pEvent.bEventPlay = false;
			}
		}
	}
}