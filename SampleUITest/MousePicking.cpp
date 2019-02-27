#include "MousePicking.h"
void MousePicking::SetMatrix(D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj,
	POINT& ptCursor, const float fWidth, const float fHeight)
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProj);
	if (matWorld != NULL)
	{
		m_matWorld = *matWorld;
	}
	if (matView != NULL)
	{
		m_matView = *matView;
	}
	if (matProj != NULL)
	{
		m_matProj = *matProj;
	}
	Update(ptCursor, fWidth, fHeight);
}

void MousePicking::Update(POINT& ptCursor, const float fWidth, const float fHeight)
{
	/* 스크린좌표의 마우스 */
	//ScreenToClient(g_hWnd, &ptCursor);

	/* ViewPort행렬의 역행렬, Proj행렬의 역행렬 = 뷰좌표계의 마우스 */
	/* ViewMatrix = ViewMatrix * InvViewPort * InvProjection */
	D3DXVECTOR3 v;
	v.x = (((2.0f * ptCursor.x) / fWidth) - 1) / m_matProj._11;
	v.y = -(((2.0f * ptCursor.y) / fHeight) - 1) / m_matProj._22;
	v.z = 1.0f;

	// Get the inverse view matrix
	// 월드가 변환되었다면 버텍스버퍼도 곱해야 한다. 그러나 피킹버텍스는 월드행렬이 곱해지지 않은
	// 버텍스버퍼(노칼좌표)에서 갖고 계산하기 때문에 정점의 좌표가 다르게 된다. 
	// 결국 버텍스버퍼의 정점을 행렬로 곱해서 광선과 계산하거나( 뷰행렬만 인버스한다. )
	// 광선을 변환해야만 된다.( 뷰행렬도 인버스 해야한다.)
	// 여기서는 광선을 변환하여 동일한 좌표계로 처리하고 있다.
	// 특별한 경우가 아니라면 단위행렬를 월드행렬로 사용해라.
	D3DXMATRIX mWorldView = m_matWorld * m_matView;
	D3DXMATRIX m;
	D3DXMatrixInverse(&m, nullptr, &mWorldView);

	/* Local = view * InvWorldView */
	m_vOrigin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vDirection = D3DXVECTOR3(v.x, v.y, v.z);
	D3DXVec3TransformCoord(&m_vOrigin, &m_vOrigin, &m);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &m);
	D3DXVec3Normalize(&m_vDirection, &m_vDirection);
}
bool MousePicking::ChkPick(D3DXVECTOR3& v0, D3DXVECTOR3& v1, D3DXVECTOR3& v2)
{
	FLOAT fBary1, fBary2;
	FLOAT fDist;
	// Check if the pick ray passes through this point
	if (IntersectTriangle(m_vOrigin, m_vDirection, v0, v1, v2,
		&fDist, &fBary1, &fBary2))
	{
		return true;
	}

	return false;
}
bool MousePicking::IntersectTriangle(const D3DXVECTOR3& orig, const D3DXVECTOR3& dir,
	D3DXVECTOR3& v0, D3DXVECTOR3& v1, D3DXVECTOR3& v2,
	FLOAT* t, FLOAT* u, FLOAT* v)
{
	D3DXVECTOR3 edge1 = v1 - v0;
	D3DXVECTOR3 edge2 = v2 - v0;

	D3DXVec3Cross(&pvec, &dir, &edge2);

	/* u >= 0.0f, v >= 0.0f, u + v < 1.0f */
	FLOAT det = D3DXVec3Dot(&edge1, &pvec);

	if (det > 0)
	{
		tvec = orig - v0;
	}
	else
	{
		tvec = v0 - orig;
		det = -det;
	}

	if (det < 0.0001f)
		return false;

	*u = D3DXVec3Dot(&tvec, &pvec);
	if (*u < 0.0f || *u > det)
		return false;

	D3DXVec3Cross(&qvec, &tvec, &edge1);

	*v = D3DXVec3Dot(&dir, &qvec);
	if (*v < 0.0f || *u + *v > det)
		return false;

	*t = D3DXVec3Dot(&edge2, &qvec);
	FLOAT fInvDet = 1.0f / det;
	*t *= fInvDet;
	*u *= fInvDet;
	*v *= fInvDet;
	return true;
}
MousePicking::MousePicking()
{
}


MousePicking::~MousePicking()
{
}
