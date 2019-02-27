#include "JArrow.h"
bool JArrow::Frame()
{
	if (m_bAttack)
	{
		m_CenterPos.x += g_fSecPerFrame * 500.0f;
		m_rtCollision.left = m_CenterPos.x;
		m_rtCollision.top = m_CenterPos.y;
		m_rtCollision.right = m_rt.bottom + m_CenterPos.x;
		m_rtCollision.bottom = m_rt.bottom + m_CenterPos.y;
		if (m_CenterPos.x >= g_rtWindow.right)
		{
			m_bAttack = false;
			m_CenterPos.x = 1000.0f;
			m_CenterPos.y = 1000.0f;
		}
	}
	else
	{
		m_bAttack = false;
		m_CenterPos.x = 1000.0f;
		m_CenterPos.y = 1000.0f;
	}
	return true;
}
JArrow::JArrow()
{
	m_bAttack = false;
}


JArrow::~JArrow()
{
}
