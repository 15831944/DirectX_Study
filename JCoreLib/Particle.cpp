#include "Particle.h"
#include "JTimer.h"

Particle::Particle()
{
	float fRand = (rand() % 300) / 3.141592f;
	m_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); // 시작위치 벡터
	m_vAdd = D3DXVECTOR3(cos(fRand), 1.0f, sin(fRand)); // 초당 이동벡터
	m_vColor.x = (float)(rand() % RAND_MAX) / RAND_MAX; // 컬러
	m_vColor.y = (float)(rand() % RAND_MAX) / RAND_MAX; // 컬러
	m_vColor.z = (float)(rand() % RAND_MAX) / RAND_MAX; // 컬러
	m_vColor.w = 1.0f; // 컬러
	m_fElapseTime = 0.0f; // 누적시간
	m_fLifeTime = (float)(rand() % 30) / 3.141592f; // 생명주기
	m_bRender = false;
}


Particle::~Particle()
{
}
