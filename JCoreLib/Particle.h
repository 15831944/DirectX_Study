#pragma once
#include "Sprite.h"
#define MAX_PARTICLE 512
class Particle
{
public:
	Sprite* m_pSprite;
public:
	D3DXVECTOR3 m_vPos; // ������ġ ����
	D3DXVECTOR3 m_vAdd; // �ʴ� �̵�����
	D3DXVECTOR4 m_vColor; // �÷�
	float m_fElapseTime; // �����ð�
	float m_fLifeTime; // �����ֱ�
	bool m_bRender;
public:
	Particle();
	virtual ~Particle();
};

