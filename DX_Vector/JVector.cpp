#include "JVector.h"
//-----------------------------------------------------------
//------------------------VECTOR3----------------------------
//-----------------------------------------------------------
Vector3 Vector3::operator + (Vector3 const &v0)
{
	return Vector3(v0.x + x, v0.y + y, v0.z + z);
}
Vector3 Vector3::operator - (Vector3 const &v0)
{
	return Vector3(x - v0.x, y - v0.y, z - v0.z);
}
Vector3 Vector3::operator * (float const &fScala)
{
	return Vector3(fScala*x, fScala*y, fScala*z);
}
Vector3 Vector3::operator + (float const &fScala)
{
	return Vector3(fScala + x, fScala + y, fScala + z);
}
Vector3 Vector3::operator / (float const &fScala)
{
	float fInvert = 1.0f / fScala;
	return Vector3(x*fInvert, y*fInvert, z*fInvert);
}
float Vector3::operator | (Vector3 const &v0)
{
	return x * v0.x + y * v0.y + z * v0.z;
}
Vector3 Vector3::operator ^ (Vector3 const &v0)
{
	return Vector3((y*v0.z - z * v0.y), (z*v0.x - x * v0.z), (x*v0.y - y * v0.x));
}
float Vector3::LengthSquared()
{
	return (x*x + y * y + z * z);
}
float Vector3::Length()
{
	return (float)sqrt(LengthSquared());
}
Vector3 Vector3::Normal()
{
	float invertLength = 1.0f / Length();
	return Vector3(x*invertLength, y*invertLength, z*invertLength);
}
float Vector3::Angle(Vector3& v0)
{

}
Vector3::Vector3(float fX, float fY, float fZ)
{
	x = fX; y = fY; z = fZ;
}
Vector3::Vector3(const Vector3& v0)
{
	x = v0.x;
	y = v0.y;
	z = v0.z;
}
Vector3::Vector3()
{
	x = y = z = 0;
}
Vector3::~Vector3()
{

}
//-----------------------------------------------------------
//------------------------VECTOR2----------------------------
//-----------------------------------------------------------
Vector2::Vector2()
{
	x = y = 0;
}
Vector2::Vector2(float fX, float fY)
{
	x = fX; y = fY;
}
Vector2::Vector2(const Vector2& v0)
{
	x = v0.x;
	y = v0.y;
}
Vector2::~Vector2()
{

}
//-----------------------------------------------------------
//------------------------VECTOR4----------------------------
//-----------------------------------------------------------
Vector4::Vector4()
{
	x = y = z = w = 0;
}
Vector4::Vector4(float fX, float fY, float fZ, float fW)
{
	x = fX; y = fY; z = fZ; w = fW;
}
Vector4::Vector4(const Vector4& v0)
{
	x = v0.x;
	y = v0.y;
	z = v0.z;
	w = v0.w;
}
Vector4::~Vector4()
{

}
