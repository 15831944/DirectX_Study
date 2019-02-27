#include "JCore.h"
#include "Particle.h"
#define MAX_PARTICLE 512
class Sample : public JCore
{
public:
	Particle* particle;
	Sprite sprite;
public:
	bool Init()
	{
		particle = new Particle[MAX_PARTICLE]();
		sprite.Init();
		vector<T_STR> vStr;
		T_STR str = L"../../Data/Effect/particle.dds";
		vStr.push_back(str);

		vector<T_STR> EffectList;
		for (int iTex = 0; iTex < 18; iTex++)
		{
			TCHAR pBuffer[50];
			if (iTex < 10)
				_stprintf_s(pBuffer, L"../../Data/Effect/sou0%d.dds", iTex);
			else
				_stprintf_s(pBuffer, L"../../Data/Effect/sou%d.dds", iTex);
			EffectList.push_back(pBuffer);
		}
		TCHAR pBuffer[50];
		//_stprintf_s(pBuffer, L"../../Data/4c1efd84a7c840d43fdc814a191e83fe.png");
		EffectList.push_back(pBuffer);
		sprite.SetTextureArray(EffectList);
		sprite.SetRectAnimation(1.0f);

		return true;
	}
	bool Frame()
	{
		GetContext()->OMSetDepthStencilState(JState::g_pDisableDSS, 0x00);
		sprite.Frame(GetContext(), I_Timer.m_fGameTimer, g_fSecPerFrame);
		for (int iParticle = 0; iParticle < MAX_PARTICLE; iParticle++)
		{
			particle[iParticle].m_bRender = true;
			particle[iParticle].m_vPos += (g_fSecPerFrame * particle[iParticle].m_vAdd);
			particle[iParticle].m_fElapseTime += g_fSecPerFrame;
			float fTime = particle[iParticle].m_fElapseTime / particle[iParticle].m_fLifeTime;
			particle[iParticle].m_vColor.w = 1.0f;
			if (particle[iParticle].m_fElapseTime >= particle[iParticle].m_fLifeTime)
			{
				float fRand = (rand() % 300) / 3.141592f;
				particle[iParticle].m_bRender = false;
				particle[iParticle].m_fElapseTime = 0.0f;
				particle[iParticle].m_vAdd = D3DXVECTOR3(cos(fRand), 1.0f, sin(fRand));
				particle[iParticle].m_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
		return true;
	}
	bool Render()
	{
		D3DXMATRIX matSpriteWorld, matTrans;
		for (int iParticle = 0; iParticle < MAX_PARTICLE; iParticle++)
		{
			if (particle[iParticle].m_bRender == false) continue;
			//sprite.m_cbData..m_cbData.Color = particle[iParticle].m_vColor;
			D3DXMatrixTranslation(&matTrans, 
				particle[iParticle].m_vPos.x,
				particle[iParticle].m_vPos.y,
				particle[iParticle].m_vPos.z);

			//matSpriteWorld = m_matBillboard * matTrans;
			sprite.SetMatrix(&matTrans, &m_MainCam->m_matView, &m_MainCam->m_matProj);
			sprite.Render(GetContext());
		}
		return true;
	}
	bool Release()
	{
		return true;
	}
};
RUN;