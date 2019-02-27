#pragma once
#include "JToken.h"
const static char* TitleName[] =
{
	"SCENE",
	"MATERIAL_LIST",
	"GEOMOBJECT",
	"HELPEROBJECT"
};
enum TITLE
{
	SCENE = 0,
	MATERIAL, 
	GEOMETRY, 
	HELPEROBJECT,
};
const static char* Scene[] =
{
	"SCENE_FIRSTFRAME",
	"SCENE_LASTFRAME",
	"SCENE_FRAMESPEED",
	"SCENE_TICKSPERFRAME"
};
enum SCENE
{
	FIRSTFRAME = 100,
	LASTFRAME,
	FRAMESPEED,
	TICKPERFRAME,
};
//const static char* Material[] =
//{
//
//};
//const static char* Geometry[] =
//{
//
//};
//const static char* HelperObject[] =
//{
//
//};
class JPaser : public JToken
{
public:
public:
	bool Load();
	bool Load(const TCHAR* pszFileName);
public:
	JPaser();
	virtual ~JPaser();
};

