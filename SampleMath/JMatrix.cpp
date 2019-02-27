#include "JMatrix.h"
void JMatrix::Translation(Vector3 const &vector)
{
	_41 = vector.x; _42 = vector.y; _43 = vector.z;
}
void JMatrix::Translation(float x, float y, float z)
{
	_41 = x; _42 = y; _43 = z;
}
void JMatrix::Scales(Vector3 const &vector)
{
	_11 = vector.x; _22 = vector.y; _33 = vector.z;
}
void JMatrix::Scales(float x, float y, float z)
{
	_11 = x; _22 = y; _33 = z;
}
void JMatrix::RotateX(float fRadian)
{
	float cosine = (float)cos(fRadian);
	float sine = (float)sin(fRadian);

	_22 = cosine; _23 = sine; 
	_32 = -sine; _33 = cosine;
}
void JMatrix::RotateY(float fRadian)
{
	float cosine = (float)cos(fRadian);
	float sine = (float)sin(fRadian);

	_11 = cosine; _13 = -sine;
	_31 = sine; _33 = cosine;
}
void JMatrix::RotateZ(float fRadian)
{
	float cosine = (float)cos(fRadian);
	float sine = (float)sin(fRadian);

	_11 = cosine; _12 = sine;
	_21 = -sine; _22 = cosine;
}
void JMatrix::ObjectLookAt(Vector3& vPosition, Vector3& vTarget, Vector3& vUp)
{
	// vLook
	Vector3 vDirection = vTarget - vPosition;
	vDirection.Normal();
	// Dir 과 직각이되는 사잇각 찾음
	float fDot = vUp | vDirection;
	// vUp(0,1,0) -> fDot(Dir과 직각)만큼 y축이변함 = (rear)UpVector
	Vector3 vUpVector = vUp - (vDirection * fDot);
	vUpVector.Normal();
	// vUp X vLook = 두개 동시에 직교하는 새로운 벡터 = vRight
	Vector3 vRightVector = vUpVector ^ vDirection;
	// Target을 바라보는 행렬?
	_11 = vRightVector.x;	_12 = vRightVector.y;	_13 = vRightVector.z;
	_21 = vUpVector.x;		_22 = vUpVector.y;		_23 = vUpVector.z;
	_31 = vDirection.x;		_32 = vDirection.y;		_33 = vDirection.z;
	_41 = vPosition.x;   	_42 = vPosition.y;      _43 = vPosition.z;
}
JMatrix JMatrix::ViewLookAt(Vector3& vPosition, Vector3& vTarget, Vector3& vUp)
{
	JMatrix matrix;
	// vLook
	Vector3 vDirection = vTarget - vPosition;
	vDirection.Normal();
	// Dir 과 직각이되는 사잇각 찾음
	float fDot = vUp | vDirection;
	// vUp(0,1,0) -> fDot(Dir과 직각)만큼 y축이변함 = (rear)UpVector
	Vector3 vUpVector = vUp - (vDirection * fDot);
	vUpVector.Normal();
	// vUp X vLook = 두개 동시에 직교하는 새로운 벡터 = vRight
	Vector3 vRightVector = vUpVector ^ vDirection;
	// Target을 바라보는 행렬?
	_11 = vRightVector.x;	_12 = vRightVector.y;	_13 = vRightVector.z;
	_21 = vUpVector.x;		_22 = vUpVector.y;		_23 = vUpVector.z;
	_31 = vDirection.x;		_32 = vDirection.y;		_33 = vDirection.z;
	_41 = -(vPosition.x*_11 + vPosition.y*_21 + vPosition.z*_31);
	_42 = -(vPosition.x*_12 + vPosition.y*_22 + vPosition.z*_32);
	_43 = -(vPosition.x*_13 + vPosition.y*_23 + vPosition.z*_33);
	memcpy(matrix, this, 16 * sizeof(float));
	return matrix;
}
JMatrix JMatrix::Transpose()
{
	JMatrix Output;
	Output._11 = _11; Output._12 = _21; Output._13 = _31; Output._14 = _41;
	Output._21 = _12; Output._22 = _22; Output._23 = _32; Output._24 = _42;
	Output._31 = _13; Output._32 = _23; Output._33 = _33; Output._34 = _43;
	Output._41 = _14; Output._42 = _24; Output._43 = _34; Output._44 = _44;
	return Output;
}
JMatrix JMatrix::operator * (JMatrix const &matrix)
{
	JMatrix Output;
	for (int iColumn = 0; iColumn < 4; iColumn++)
	{
		for (int iRow = 0; iRow < 4; iRow++)
		{
			Output.m[iRow][iColumn] = m[iRow][0] * matrix.m[0][iColumn] +
									  m[iRow][1] * matrix.m[1][iColumn] +
									  m[iRow][2] * matrix.m[2][iColumn] +
									  m[iRow][3] * matrix.m[3][iColumn];
		}
	}
	return Output;
}
Vector3 JMatrix::operator * (Vector3 const &vector)
{
	return Vector3(
		vector.x * _11 + vector.y * _21 + vector.z * _31 + _41, 
		vector.x * _12 + vector.y * _22 + vector.z * _32 + _42, 
		vector.x * _13 + vector.y * _23 + vector.z * _33 + _43);
}

void JMatrix::Identity()
{
	_12 = _13 = _14 = 0.0f;
	_21 = _23 = _24 = 0.0f;
	_31 = _32 = _34 = 0.0f;
	_41 = _42 = _43 = 0.0f;
	_11 = _22 = _33 = _44 = 1.0f;
}
JMatrix::JMatrix()
{
	Identity();
}
JMatrix::JMatrix(const JMatrix& matrix)
{
	_11 = matrix._11; _12 = matrix._12; _13 = matrix._13; _14 = matrix._14;
	_21 = matrix._21; _22 = matrix._22; _23 = matrix._23; _24 = matrix._24;
	_31 = matrix._31; _32 = matrix._32; _33 = matrix._33; _34 = matrix._34;
	_41 = matrix._41; _42 = matrix._42; _43 = matrix._43; _44 = matrix._44;
}
JMatrix::~JMatrix()
{

}
