#pragma once
#include "JDxObject.h"
using namespace DX;
struct JInstance
{
	D3DXMATRIX m_matWorld;
	D3DXVECTOR4 m_vColor;
};
class Instance
{
public:
	JDxObject m_dxObj;
	VSCB	m_cbData;
	ID3D11Buffer* m_pInstanceBuffer;
	bool m_bInstanced;
public:
	bool InstFrame(ID3D11DeviceContext* context, int iSize, Instance* pInstanceList);
	bool PostRender(ID3D11DeviceContext* context, UINT iSize);
	bool SetInstance(Instance* pInstanceList);
	bool SetInputLayOut();
public:
	Instance();
	virtual ~Instance();
};

namespace INSTANCE
{
	bool SetInstance(JDxObject& Obj, Instance* pInstanceList);
}