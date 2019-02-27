#include "JPaser.h"

bool JPaser::Load(const TCHAR* pszFileName)
{
	if (!AseLoad(pszFileName)) return false;
	if (!Load()) return false;
	
return true;
}
bool JPaser::Load()
{
	while (m_dwTknIndex + 1 < m_pTokenList.size())
	{
		int iType = SearchArray(4, TitleName);
		switch (iType)
		{
		case SCENE:
		{

		}break;
		case MATERIAL:
		{

		}break;
		case GEOMETRY:
		{

		}break;
		case HELPEROBJECT:
		{

		}break;
		default:
		{
			return false;
		}break;
		}
	}
	return true;
}
JPaser::JPaser()
{

}


JPaser::~JPaser()
{
}
