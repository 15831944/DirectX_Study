#include "Parser.h"
AnimTrack* Parser::SetDoublyLinkedList(AnimTrack* pCurrentTrack, AnimTrack* pPrev)
{
	if (pPrev)
	{
		pPrev->NextTrack = pCurrentTrack;
		pCurrentTrack->PrevTrack = pPrev;
	}
	return pCurrentTrack;
}
bool Parser::Load()
{
	INT iLine;
	if (!LoadTemp()) return false;
	if (!LoadScene()) return false;
	if (!LoadMaterial()) return false;
	if (!LoadObject()) return false;
	for (int iGeom = 0; iGeom < m_Geom.size(); iGeom++)
	{
		SetAnimation(m_Geom[iGeom]);
	}
	if (!Convert())return false;
	return true;
}
vector<JMesh*> Parser::GetData()
{
	return m_pMeshList;
}
bool Parser::clear()
{
	m_pMeshList.clear();
	m_Tokenlist.clear();
	m_CurrentToken.clear();
	SAFE_DELETE(m_pData);
	for (int iMtrl = 0; iMtrl < m_Mtrl.size(); iMtrl++)
	{
		m_Mtrl[iMtrl].subMtrl.clear();
		m_Mtrl[iMtrl].tex.clear();
	}
	m_Mtrl.clear();
	return true;
}
bool Parser::LoadTemp()
{
	INT iLine = 0;
	if (iLine = FindToken("READ_END"))	{	}
	return true;
}
bool Parser::LoadScene()
{
	INT iLine = 0;
	char szTemp[256] = { 0, };
	if (iLine = FindToken("SCENE"))
	{
		sscanf(m_Tokenlist[iLine].c_str(), "%s%d%d%d%d", szTemp, &m_Scene.iFirstFrame, &m_Scene.iLastFrame, &m_Scene.iFrameSpeed, &m_Scene.iTickPerFrame);
	}
	return true;
}
bool Parser::LoadMaterial()
{
	INT iLine = 0;
	char szTemp[256] = { 0, };
	int NumMtrl = 0;
	if ((iLine = FindToken("ROOT_MATERIAL")) > 0)
	{
		sscanf(m_Tokenlist[iLine].c_str(), "%s%d", szTemp, &NumMtrl);
		m_Mtrl.resize(NumMtrl);
	}
	for (int iMtrl = 0; iMtrl < NumMtrl; iMtrl++)
	{
		if ((iLine = FindToken("MATERIAL")) > 0)
		{
			if ((iLine = FindToken("MTRLNAME")) > 0)
			{
				sscanf(m_Tokenlist[iLine].c_str(), "%s %s",szTemp, m_Mtrl[iMtrl].strMtrlName.c_str());
			}
			if ((iLine = FindToken("CLASSNAME")) > 0)
			{
				sscanf(m_Tokenlist[iLine].c_str(), "%s%s", szTemp, m_Mtrl[iMtrl].strMtrlClass.c_str());
			}
			if ((iLine = FindToken("NUMSUBMTRL")) > 0)
			{
				sscanf(m_Tokenlist[iLine].c_str(), "%s%d", szTemp , &m_Mtrl[iMtrl].iSubMtrl);
				m_Mtrl[iMtrl].subMtrl.resize(m_Mtrl[iMtrl].iSubMtrl);
			}
			// submtrl
			for (int iSubMtrl = 0; iSubMtrl < m_Mtrl[iMtrl].iSubMtrl; iSubMtrl++)
			{
				if ((iLine = FindToken("SUBMATERIAL")) > 0)
				{
					if ((iLine = FindToken("MTRLNAME")) > 0)
					{
						sscanf(m_Tokenlist[iLine].c_str(), "%s%s", szTemp , m_Mtrl[iMtrl].subMtrl[iSubMtrl].strMtrlName.c_str());
					}
					if ((iLine = FindToken("CLASSNAME")) > 0)
					{
						sscanf(m_Tokenlist[iLine].c_str(), "%s%s", szTemp, m_Mtrl[iMtrl].subMtrl[iSubMtrl].strMtrlClass.c_str());
					}
					if ((iLine = FindToken("NUMSUBMTRLS")) > 0)
					{
						sscanf(m_Tokenlist[iLine].c_str(), "%s%d", szTemp , &m_Mtrl[iMtrl].subMtrl[iSubMtrl].iSubMtrl);
					}
					if ((iLine = FindToken("NUMTEXMAP")) > 0)
					{
						int iTex = 0;
						sscanf(m_Tokenlist[iLine].c_str(), "%s%d", szTemp , &iTex);
						m_Mtrl[iMtrl].subMtrl[iSubMtrl].tex.resize(iTex);
						for (int iTexture = 0; iTexture < iTex; iTexture++)
						{
							if ((iLine = FindToken("TEXMAPTYPE")) > 0)
							{
								sscanf(m_Tokenlist[iLine].c_str(), "%s%d", szTemp, &m_Mtrl[iMtrl].subMtrl[iSubMtrl].tex[iTexture].iType);
							}
							if ((iLine = FindToken("TEXTURENAME")) > 0)
							{
								sscanf(m_Tokenlist[iLine].c_str(), "%s%s", szTemp, m_Mtrl[iMtrl].subMtrl[iSubMtrl].tex[iTexture].strTexName.c_str());
							}
						}
					}
				}
			}
		}
	}
	--m_dwTokenIndex;
	return true;
}
bool Parser::LoadObject()
{
	INT iLine = 0;
	char szTemp[256] = { 0, };

	while (m_dwTokenIndex < m_dwMaxTokenLine)
	{
		ASE_GEOMETRY* Geom = new ASE_GEOMETRY();
		if ((iLine = FindToken("OBJECTS")) > 0)
		{
			if ((iLine = FindToken("NODENAME")) > 0)
			{
				sscanf(m_Tokenlist[iLine].c_str(), "%s%s", szTemp, Geom->strNodeName.c_str());
			}
			if ((iLine = FindToken("PARENT")) > 0)
			{
				sscanf(m_Tokenlist[iLine].c_str(), "%s%s", szTemp, Geom->strParentName.c_str());
			}
			if ((iLine = FindToken("CLASSTYPE")) > 0)
			{
				sscanf(m_Tokenlist[iLine].c_str(), "%s%d", szTemp, &Geom->iClassType);
			}
			if ((iLine = FindToken("NUMFACE")) > 0)
			{
				sscanf(m_Tokenlist[iLine].c_str(), "%s%d", szTemp, &Geom->m_dwFaceSize);
			}
			if ((iLine = FindToken("NUMTRI")) > 0)
			{
				sscanf(m_Tokenlist[iLine].c_str(), "%s%d", szTemp, &Geom->iNumTri);
			}
			if ((iLine = FindToken("NUMPOS")) > 0)
			{
				sscanf(m_Tokenlist[iLine].c_str(), "%s%d", szTemp, &Geom->iNumPos);
			}
			if ((iLine = FindToken("NUMROT")) > 0)
			{
				sscanf(m_Tokenlist[iLine].c_str(), "%s%d", szTemp, &Geom->iNumRot);
			}
			if ((iLine = FindToken("NUMSCL")) > 0)
			{
				sscanf(m_Tokenlist[iLine].c_str(), "%s%d", szTemp, &Geom->iNumScl);
			}
			if ((iLine = FindToken("REF")) > 0)
			{
				sscanf(m_Tokenlist[iLine].c_str(), "%s%d", szTemp, &Geom->iGeomMtrlRef);
			}
			if ((iLine = FindToken("MATRIXWORLD")) > 0)
			{
				sscanf(m_Tokenlist[iLine].c_str(), "%s%f%f%f%f %f%f%f%f %f%f%f%f %f%f%f%f", szTemp, 
					&Geom->m_matWorld._11, &Geom->m_matWorld._12, &Geom->m_matWorld._13, &Geom->m_matWorld._14, 
					&Geom->m_matWorld._21, &Geom->m_matWorld._22, &Geom->m_matWorld._23, &Geom->m_matWorld._24, 
					&Geom->m_matWorld._31, &Geom->m_matWorld._32, &Geom->m_matWorld._33, &Geom->m_matWorld._34, 
					&Geom->m_matWorld._41, &Geom->m_matWorld._42, &Geom->m_matWorld._43, &Geom->m_matWorld._44);
			}
			if ((iLine = FindToken("TRAINGLES")) > 0)
			{
				sscanf(m_Tokenlist[iLine].c_str(), "%s%d", szTemp, &Geom->iNumTri);
			}
			for (int iTri = 0; iTri < Geom->iNumTri; iTri++)
			{
				ASE_TRIANGLE tri;
				for (int i = 0; i < 3; i++)
				{
					sscanf(m_Tokenlist[++iLine].c_str(), "%f%f%f %f%f%f %f%f%f%f %f%f %d",
						&tri.v[i].p.x, &tri.v[i].p.y, &tri.v[i].p.z,
						&tri.v[i].n.x, &tri.v[i].n.y, &tri.v[i].n.z,
						&tri.v[i].c.x, &tri.v[i].c.y, &tri.v[i].c.z, &tri.v[i].c.w,
						&tri.v[i].t.x, &tri.v[i].t.y,
						&tri.dwSubID);
				}
				Geom->TriangleList.push_back(tri);
			}
			if (Geom->iNumPos > 0)
			{
				if ((iLine = FindToken("POSITION_TRACK")) > 0)
				{
					for (int iPos = 0; iPos < Geom->iNumPos; iPos++)
					{
						AnimTrack* Anim = new AnimTrack();
						sscanf(m_Tokenlist[++iLine].c_str(), "%d %f%f%f", 
							&Anim->iTick, 
							&Anim->vPos.x, &Anim->vPos.y, &Anim->vPos.z);
						Geom->m_pTransTrack.push_back(Anim);
					}
				}
			}
			if (Geom->iNumRot > 0)
			{
				if ((iLine = FindToken("ROTATION_TRACK")) > 0)
				{
					for (int iRot = 0; iRot < Geom->iNumRot; iRot++)
					{
						AnimTrack* Anim = new AnimTrack();
						sscanf(m_Tokenlist[++iLine].c_str(), "%d %f%f%f%f %f%f%f",
							&Anim->iTick,
							&Anim->vPos.x, &Anim->vPos.y, &Anim->vPos.z,
							&Anim->qRot.x, &Anim->qRot.y, &Anim->qRot.z, &Anim->qRot.w);
						Geom->m_pRotateTrack.push_back(Anim);
					}
				}
			}
			if (Geom->iNumScl > 0)
			{
				if ((iLine = FindToken("SCALE_TRACK")) > 0)
				{
					for (int iRot = 0; iRot < Geom->iNumRot; iRot++)
					{
						AnimTrack* Anim = new AnimTrack();
						sscanf(m_Tokenlist[++iLine].c_str(), "%d %f%f%f%f %f%f%f",
							&Anim->iTick,
							&Anim->vPos.x, &Anim->vPos.y, &Anim->vPos.z,
							&Anim->qRot.x, &Anim->qRot.y, &Anim->qRot.z, &Anim->qRot.w);
						Geom->m_pScaleTrack.push_back(Anim);
					}
				}
			}
		}
		m_Geom.push_back(Geom);
	}
	return true;
}
bool Parser::SetAnimation(ASE_GEOMETRY* geom)
{
	AnimTrack* pPrevTrack = NULL;
	for (int iTrack = 0; iTrack < geom->m_pTransTrack.size(); iTrack++)
	{
		AnimTrack* pTrack = new AnimTrack;
		pTrack->iTick = geom->m_pTransTrack[iTrack]->iTick;
		pTrack->vPos = geom->m_pTransTrack[iTrack]->vPos;

		pPrevTrack = SetDoublyLinkedList(pTrack, pPrevTrack);
		geom->m_pTransTrack[iTrack] = pTrack;
	}
	pPrevTrack = NULL;
	for (int iTrack = 0; iTrack < geom->m_pRotateTrack.size(); iTrack++)
	{
		AnimTrack* pTrack = new AnimTrack;

		pTrack->iTick = geom->m_pRotateTrack[iTrack]->iTick;
		pTrack->vPos = geom->m_pRotateTrack[iTrack]->vPos;
		pTrack->qRot = geom->m_pRotateTrack[iTrack]->qRot;
		pPrevTrack = SetDoublyLinkedList(pTrack, pPrevTrack);
		geom->m_pRotateTrack[iTrack] = pTrack;
	}
	pPrevTrack = NULL;
	for (int iTrack = 0; iTrack < geom->m_pScaleTrack.size(); iTrack++)
	{
		AnimTrack* pTrack = new AnimTrack;
		pTrack->iTick = geom->m_pScaleTrack[iTrack]->iTick;
		pTrack->vPos = geom->m_pScaleTrack[iTrack]->vPos;
		pTrack->qRot = geom->m_pScaleTrack[iTrack]->qRot;
		pPrevTrack = SetDoublyLinkedList(pTrack, pPrevTrack);
		geom->m_pScaleTrack[iTrack] = pTrack;
	}
	return true;
}
bool Parser::Convert()
{
	for (int iGeom = 0; iGeom < m_Geom.size(); iGeom++)
	{
		JMesh* pMesh = new JMesh();
		pMesh->m_strNodeName = m_Geom[iGeom]->strNodeName.c_str();
		pMesh->m_strParentName = m_Geom[iGeom]->strParentName.c_str();
		pMesh->m_matLocalWorld = m_Geom[iGeom]->m_matWorld;
		pMesh->m_pTransTrack = m_Geom[iGeom]->m_pTransTrack;
		pMesh->m_pRotateTrack = m_Geom[iGeom]->m_pRotateTrack;
		pMesh->m_pScaleTrack = m_Geom[iGeom]->m_pScaleTrack;
		D3DXMatrixIdentity(&pMesh->m_matCalc);
		for (int iTri = 0; iTri < m_Geom[iGeom]->TriangleList.size(); iTri++)
		{
			int iRef = m_Geom[iGeom]->iGeomMtrlRef;
			int iSubMtrlID = m_Geom[iGeom]->TriangleList[iTri].dwSubID;
			if (iRef >= 0 && iSubMtrlID < m_Mtrl[iRef].subMtrl.size())
			{
				ASE_TRIANGLE sTri = m_Geom[iGeom]->TriangleList[iTri];
				pMesh->m_pSubMeshList.resize(m_Mtrl[iRef].subMtrl.size());
				pMesh->m_pSubMeshList[iSubMtrlID].m_pTriangleList.push_back(sTri);
				pMesh->m_pSubMeshList[iSubMtrlID].m_pTexName = m_Mtrl[iRef].subMtrl[iSubMtrlID].tex[0].strTexName.c_str();
			}
		}
		for (int iSubMesh = 0; iSubMesh < pMesh->m_pSubMeshList.size(); iSubMesh++)
		{
			for (int iTri = 0; iTri < pMesh->m_pSubMeshList[iSubMesh].m_pTriangleList.size(); iTri++)
			{
				pMesh->m_pSubMeshList[iSubMesh].m_pVertexList.push_back(pMesh->m_pSubMeshList[iSubMesh].m_pTriangleList[iTri].v[0]);
				pMesh->m_pSubMeshList[iSubMesh].m_pVertexList.push_back(pMesh->m_pSubMeshList[iSubMesh].m_pTriangleList[iTri].v[1]);
				pMesh->m_pSubMeshList[iSubMesh].m_pVertexList.push_back(pMesh->m_pSubMeshList[iSubMesh].m_pTriangleList[iTri].v[2]);

				pMesh->m_pSubMeshList[iSubMesh].m_pIndexList.push_back(iTri * 3 + 0);
				pMesh->m_pSubMeshList[iSubMesh].m_pIndexList.push_back(iTri * 3 + 2);
				pMesh->m_pSubMeshList[iSubMesh].m_pIndexList.push_back(iTri * 3 + 1);
			}
		}
		m_pMeshList.push_back(pMesh);
	}
	for (int iMesh = 0; iMesh < m_pMeshList.size(); iMesh++)
	{
		JMesh* pParent = GetParent(m_pMeshList[iMesh]);
		m_pMeshList[iMesh]->m_pParent = pParent;

		D3DXMATRIX matInvParent;
		D3DXMatrixIdentity(&matInvParent);

		if (m_pMeshList[iMesh]->m_pParent)
		{
			D3DXMatrixInverse(&matInvParent, NULL, &m_pMeshList[iMesh]->m_pParent->m_matLocalWorld);
		}
		D3DXMATRIX matInverse = m_pMeshList[iMesh]->m_matLocalWorld * matInvParent;
		D3DXVECTOR3 v3Pos, v3Scale;
		D3DXQUATERNION q;
		D3DXMatrixDecompose(&v3Scale, &q, &v3Pos, &matInverse);
		D3DXMatrixScaling(&m_pMeshList[iMesh]->m_matLocalScale, v3Scale.x, v3Scale.y, v3Scale.z);
		D3DXMatrixTranslation(&m_pMeshList[iMesh]->m_matLocalTrans, v3Pos.x, v3Pos.y, v3Pos.z);
		D3DXMatrixRotationQuaternion(&m_pMeshList[iMesh]->m_matLocalRotate, &q);
	}
	return true;
}
JMesh* Parser::GetParent(JMesh* pMesh)
{
	if (pMesh->m_strParentName == "(null)") return NULL;
	for (int iMesh = 0; iMesh < m_pMeshList.size(); iMesh++)
	{
		if (m_pMeshList[iMesh]->m_strNodeName == pMesh->m_strParentName)
		{
			return m_pMeshList[iMesh];
		}
	}
	return NULL;
}
Parser::Parser()
{

}


Parser::~Parser()
{
}
