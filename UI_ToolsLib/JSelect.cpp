#include "JSelect.h"
#include "JInput.h"
#include "JWrite.h"
bool JSelect::Init()
{
	//m_Line.Init();
	return true;
}
bool JSelect::ClickCheck(JDxObject& Obj)
{
	JDxObject object = Obj;
	SetMatrix(&object.m_matWorld, &object.m_matView, &object.m_matProj);
	Update(object.m_fWidth, object.m_fHeight);
	D3DXVECTOR3 v0, v1, v2;

	for (int iFace = 0; iFace < 2; iFace++)
	{
		v0 = object.m_pVertices[object.m_pIndices[iFace * 3 + 0]].p;
		v1 = object.m_pVertices[object.m_pIndices[iFace * 3 + 1]].p;
		v2 = object.m_pVertices[object.m_pIndices[iFace * 3 + 2]].p;
		//D3DXVec3TransformCoord(&v0, &v0, &object.m_matWorld);
		//D3DXVec3TransformCoord(&v1, &v1, &object.m_matWorld);
		//D3DXVec3TransformCoord(&v2, &v2, &object.m_matWorld);


		if (I_Input.m_dwMouseState[0] == KEY_PUSH && ChkPick(v0, v1, v2))
		{
			return true;
		}
	}
	return false;
}
bool JSelect::Render(ID3D11DeviceContext* context)
{
	return true;
}
bool JSelect::Release()
{
	return true;
}
void JSelect::SetMatrix(D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj)
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

}	

void JSelect::Update(float fWidth, float fHeight)
{
	POINT ptCursor;
	GetCursorPos(&ptCursor);
	ScreenToClient(g_hWnd, &ptCursor);

	// Compute the vector of the pick ray in screen space
	D3DXVECTOR3 v;
	// 방법 1
	/*v.x =  ( ( ( 2.0f * ptCursor.x ) / TBASIS::g_iClientWidth  ) - 1 );
	v.y = -( ( ( 2.0f * ptCursor.y ) / TBASIS::g_iClientHeight ) - 1 );
	v.z =  1.0f;
	D3DXVec3TransformCoord( &v, &v, &m );*/
	// 방법 2
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
	D3DXMatrixInverse(&m, NULL, &mWorldView);

	// 방법 1
	m_Ray.vOrigin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Ray.vDirection = D3DXVECTOR3(v.x, v.y, v.z);
	D3DXVec3TransformCoord(&m_Ray.vOrigin, &m_Ray.vOrigin, &m);
	D3DXVec3TransformNormal(&m_Ray.vDirection, &m_Ray.vDirection, &m);
	D3DXVec3Normalize(&m_Ray.vDirection, &m_Ray.vDirection);
}
bool JSelect::ChkPick(D3DXVECTOR3& v0, D3DXVECTOR3& v1, D3DXVECTOR3& v2)
{
	FLOAT fBary1, fBary2;
	FLOAT fDist;
	// Check if the pick ray passes through this point
	if (IntersectTriangle(m_Ray.vOrigin, m_Ray.vDirection, v0, v1, v2,
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
bool JSelect::IntersectTriangle(const D3DXVECTOR3& orig, const D3DXVECTOR3& dir,
	D3DXVECTOR3& v0, D3DXVECTOR3& v1, D3DXVECTOR3& v2,
	FLOAT* t, FLOAT* u, FLOAT* v)
{
	// Find vectors for two edges sharing vert0
	D3DXVECTOR3 edge1 = v1 - v0;
	D3DXVECTOR3 edge2 = v2 - v0;

	// Begin calculating determinant - also used to calculate U parameter
	//D3DXVECTOR3 pvec;
	D3DXVec3Cross(&pvec, &dir, &edge2);

	// If determinant is near zero, ray lies in plane of triangle
	FLOAT det = D3DXVec3Dot(&edge1, &pvec);

	//D3DXVECTOR3 tvec; // 내적이 양수가 될 수 있도록 det 방향을 뒤집는다.
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

	// Calculate U parameter and test bounds
	*u = D3DXVec3Dot(&tvec, &pvec);
	if (*u < 0.0f || *u > det)
		return false;

	// Prepare to test V parameter
	//D3DXVECTOR3 qvec;
	D3DXVec3Cross(&qvec, &tvec, &edge1);

	// Calculate V parameter and test bounds
	*v = D3DXVec3Dot(&dir, &qvec);
	if (*v < 0.0f || *u + *v > det)
		return false;

	// Calculate t, scale parameters, ray intersects triangle
	*t = D3DXVec3Dot(&edge2, &qvec);
	FLOAT fInvDet = 1.0f / det;
	*t *= fInvDet;
	*u *= fInvDet;
	*v *= fInvDet;

	//D3DXVECTOR3 e3 = v2 - v1;
	//D3DXVECTOR3 vi = orig + (*t) * dir;
	//D3DXVECTOR3 i0 = v0 + edge1 * (*u) + edge2 * (*v);
	//
	//this->vPickRayOrig = orig;
	//this->vPickRayDir = dir;
}
JSelect::JSelect()
{
}


JSelect::~JSelect()
{
}
