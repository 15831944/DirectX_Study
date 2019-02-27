#include "Particle.h"
#include "JTimer.h"

Particle::Particle()
{
	float fRand = (rand() % 300) / 3.141592f;
	m_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); // ������ġ ����
	m_vAdd = D3DXVECTOR3(cos(fRand), 1.0f, sin(fRand)); // �ʴ� �̵�����
	m_vColor.x = (float)(rand() % RAND_MAX) / RAND_MAX; // �÷�
	m_vColor.y = (float)(rand() % RAND_MAX) / RAND_MAX; // �÷�
	m_vColor.z = (float)(rand() % RAND_MAX) / RAND_MAX; // �÷�
	m_vColor.w = 1.0f; // �÷�
	m_fElapseTime = 0.0f; // �����ð�
	m_fLifeTime = (float)(rand() % 30) / 3.141592f; // �����ֱ�
	m_bRender = false;
}


Particle::~Particle()
{
}
