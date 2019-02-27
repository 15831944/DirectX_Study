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
	/* ��ũ����ǥ�� ���콺 */
	//ScreenToClient(g_hWnd, &ptCursor);

	/* ViewPort����� �����, Proj����� ����� = ����ǥ���� ���콺 */
	/* ViewMatrix = ViewMatrix * InvViewPort * InvProjection */
	D3DXVECTOR3 v;
	v.x = (((2.0f * ptCursor.x) / fWidth) - 1) / m_matProj._11;
	v.y = -(((2.0f * ptCursor.y) / fHeight) - 1) / m_matProj._22;
	v.z = 1.0f;

	// Get the inverse view matrix
	// ���尡 ��ȯ�Ǿ��ٸ� ���ؽ����۵� ���ؾ� �Ѵ�. �׷��� ��ŷ���ؽ��� ��������� �������� ����
	// ���ؽ�����(��Į��ǥ)���� ���� ����ϱ� ������ ������ ��ǥ�� �ٸ��� �ȴ�. 
	// �ᱹ ���ؽ������� ������ ��ķ� ���ؼ� ������ ����ϰų�( ����ĸ� �ι����Ѵ�. )
	// ������ ��ȯ�ؾ߸� �ȴ�.( ����ĵ� �ι��� �ؾ��Ѵ�.)
	// ���⼭�� ������ ��ȯ�Ͽ� ������ ��ǥ��� ó���ϰ� �ִ�.
	// Ư���� ��찡 �ƴ϶�� ������ĸ� ������ķ� ����ض�.
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
