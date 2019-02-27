#pragma once
#include "JShape.h"
class JLineShape : public JShape
{
public:
	bool Init();
	bool Frame();
	bool Render(ID3D11DeviceContext* context);
	void Draw(ID3D11DeviceContext* context, D3DXVECTOR3 vPos, D3DXVECTOR3 vEnd, D3DXVECTOR4 vColor);
public:
	JLineShape();
	virtual ~JLineShape();
};