#pragma once
#include "JVector.h"
struct float4x4
{
	union
	{
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float m[4][4];
	};
};
class JMatrix : public float4x4
{
public:
	void Identity();
	JMatrix operator * (JMatrix const &matrix);
	Vector3 operator * (Vector3 const &vector);
	void Translation(Vector3 const &vector);
	void Translation(float x, float y, float z);
	void Scales(Vector3 const &vector);
	void Scales(float x, float y, float z);
	void RotateX(float fRadian);
	void RotateY(float fRadian);
	void RotateZ(float fRadian);
	void ObjectLookAt(Vector3& vPosition, Vector3& vTarget, Vector3& vUp);
	JMatrix ViewLookAt(Vector3& vPosition, Vector3& vTarget, Vector3& vUp);
	JMatrix Transpose();
public:
	JMatrix();
	JMatrix(const JMatrix& matrix);
	virtual ~JMatrix();
};