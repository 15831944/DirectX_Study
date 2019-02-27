#pragma once
#include "Sprite.h"
#define MAX_PARTICLE 512
class Particle
{
public:
	Sprite* m_pSprite;
public:
	D3DXVECTOR3 m_vPos; // 시작위치 벡터
	D3DXVECTOR3 m_vAdd; // 초당 이동벡터
	D3DXVECTOR4 m_vColor; // 컬러
	float m_fElapseTime; // 누적시간
	float m_fLifeTime; // 생명주기
	bool m_bRender;
public:
	Particle();
	virtual ~Particle();
};

