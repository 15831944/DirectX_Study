#include "MousePicking.h"
bool MousePicking::Init()
{
	m_Line.Init();
	return true;
}
bool MousePicking::Render(ID3D11DeviceContext* context)
{
	PC_VERTEX PC_V[]
	{
		{ m_rRay.vDirection, D3DXVECTOR4(1.0f,0.0f,1.0f,0.0f) },
		{ m_rRay.vOrigin, D3DXVECTOR4(1.0f,0.0f,1.0f,0.0f) },
	};
	context->UpdateSubresource(m_Line.m_dxObj.m_pVertexBuffer, 0, 0, PC_V, 0, 0);
	m_Line.SetMatrix(NULL, &m_matView, &m_matProj);
	m_Line.Render(context);
	return true;
}
bool MousePicking::Release()
{
	return true;
}
void MousePicking::SetMatrix(D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj)
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProj);
	if (matWorld != NULL)
	{
		m_matWorld = *matWorld;
		m_vCentor.x = m_matWorld._41;
		m_vCentor.y = m_matWorld._42;
		m_vCentor.z = m_matWorld._43;
	}
	if (matView != NULL)
	{
		m_matView = *matView;
	}
	if (matProj != NULL)
	{
		m_matProj = *matProj;
	}
	Update();
}

void MousePicking::Update()
{
	/* ��ũ����ǥ�� ���콺 */
	POINT ptCursor;
	GetCursorPos(&ptCursor);
	ScreenToClient(g_hWnd, &ptCursor);

	/* ViewPort����� �����, Proj����� ����� = ����ǥ���� ���콺 */
	/* ViewMatrix = ViewMatrix * InvViewPort * InvProjection */
	D3DXVECTOR3 v;
	v.x = (((2.0f * ptCursor.x) / g_rtClient.right) - 1) / m_matProj._11;
	v.y = -(((2.0f * ptCursor.y) / g_rtClient.bottom) - 1) / m_matProj._22;
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
	D3DXMatrixInverse(&m, NULL, &mWorldView);

	/* Local = view * InvWorldView */
	m_rRay.vOrigin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rRay.vDirection = D3DXVECTOR3(v.x, v.y, v.z);
	D3DXVec3TransformCoord(&m_rRay.vOrigin, &m_rRay.vOrigin, &m);
	D3DXVec3TransformNormal(&m_rRay.vDirection, &m_rRay.vDirection, &m);
	D3DXVec3Normalize(&m_rRay.vDirection, &m_rRay.vDirection);
}
bool MousePicking::ChkPick(D3DXVECTOR3& v0, D3DXVECTOR3& v1, D3DXVECTOR3& v2)
{
	FLOAT fBary1, fBary2;
	FLOAT fDist;
	// Check if the pick ray passes through this point
	if (IntersectTriangle(m_rRay.vOrigin, m_rRay.vDirection, v0, v1, v2,
		&fDist, &fBary1, &fBary2))
	{
		m_vSrcVex[0] = v0;
		m_vSrcVex[1] = v1;
		m_vSrcVex[2] = v2;
		m_matWorldPick = m_matWorld;
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
