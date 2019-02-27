#include "JCore.h"
#include "Particle.h"
#define MAX_PARTICLE 10000
class Sample : public JCore
{
public:
	vector<Particle> particle;
	Sprite sprite;
	D3DXMATRIX matSpriteWorld, matTrans;
public:
	bool Init()
	{
		particle.resize(MAX_PARTICLE);
		sprite.Create(true, "PS", "VS", L"Instance.hlsl");

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

		D3DXMATRIX matTrans;
		sprite.m_pInstance.resize(MAX_PARTICLE);
		for (int iPlane = 0; iPlane < MAX_PARTICLE; iPlane++)
		{
			Particle par;
			D3DXMatrixTranslation(&matTrans, par.m_vPos.x,
				par.m_vPos.y,
				par.m_vPos.z);
			sprite.m_pInstance[iPlane].matWorld = matTrans;
			sprite.m_pInstance[iPlane].vColor = par.m_vColor;
			particle[iPlane] = par;
		}
		sprite.SetTextureArray(EffectList);
		sprite.SetRectAnimation(1.0f);

		sprite.m_pInstanceBuffer = DX::CreateVertexBuffer(g_pd3dDevice, &sprite.m_pInstance.at(0), sizeof(Instance), MAX_PARTICLE, true);
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

			D3DXMatrixTranslation(&matTrans,
				particle[iParticle].m_vPos.x,
				particle[iParticle].m_vPos.y,
				particle[iParticle].m_vPos.z);
			sprite.m_pInstance[iParticle].matWorld = matTrans;
			sprite.m_pInstance[iParticle].vColor = particle[iParticle].m_vColor;
		}
		if (sprite.m_bInstanced)
		{
			Instance* pInstance = NULL;
			D3D11_MAPPED_SUBRESOURCE MappedFaceDest;
			if (SUCCEEDED(GetContext()->Map((ID3D11Resource*)sprite.m_pInstanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedFaceDest)))
			{
				pInstance = (Instance*)MappedFaceDest.pData;
				memcpy(pInstance, &sprite.m_pInstance.at(0), sizeof(Instance) * particle.size());
				GetContext()->Unmap(sprite.m_pInstanceBuffer, 0);
			}
		}
		return true;
	}
	bool Render()
	{
		sprite.SetMatrix(&matTrans, &m_MainCam->m_matView, &m_MainCam->m_matProj);
		sprite.RenderInstancing(GetContext());
		return true;
	}
	bool Release()
	{
		return true;
	}
};
RUN;