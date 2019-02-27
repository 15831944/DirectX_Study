#pragma once
#include "math.h"
struct float2
{
	union
	{
		struct { float x, y; };
		float v[2];
	};
};
struct float3
{
	union
	{
		struct { float x, y, z; };
		float v[3];
	};
};
struct float4
{
	union
	{
		struct { float x, y, z, w; };
		float v[4];
	};
};
class Vector2 : public float2
{
public:
	Vector2();
	Vector2(const Vector2& v0);
	Vector2(float fX, float fY);
};
class Vector3 : public float3
{
public:
	Vector3();
	Vector3(float fX, float fY, float fZ);
	Vector3(const Vector3& v0);
public:
	Vector3 operator + (Vector3 const &v0);
	Vector3 operator - (Vector3 const &v0);
	Vector3 operator * (float const &fScala);
	Vector3 operator + (float const &fScala);
	Vector3 operator / (float const &fScala);
	float operator | (Vector3 const &v0);
	Vector3 operator ^ (Vector3 const &v0);
	float LengthSquared();
	float Length();
	Vector3 Normal();
};
class Vector4 : public float4
{
public:
	Vector4();
	Vector4(const Vector4& v0);
	Vector4(float fX, float fY, float fZ, float fW);
};