#include "JTransform.h"
namespace UI
{
	bool JTransform::UpdateTransform()
	{
		if (m_pCurTransform == nullptr) return false;
		m_pCurTransform->m_vScl = this->m_vScl;
		m_pCurTransform->m_vRot = this->m_vRot;
		m_pCurTransform->m_vPos = this->m_vPos;
		return true;
	}
	void JTransform::Translate(const float& fx, const float& fy, const float& fz)
	{
		m_vPos.x += fx;
		m_vPos.y += fy;
		m_vPos.z += fz;
		UpdateTransform();
	}
	void JTransform::Rotate(const float& fx, const float& fy, const float& fz)
	{
		m_vRot.x += fx;
		m_vRot.y += fy;
		m_vRot.z += fz;
		UpdateTransform();
	}
	void JTransform::Scale(const float& fx, const float& fy, const float& fz)
	{
		m_vScl.x += fx;
		m_vScl.y += fy;
		m_vScl.z += fz;
		UpdateTransform();
	}
	JTransform::JTransform()
	{
	}


	JTransform::~JTransform()
	{
	}
}