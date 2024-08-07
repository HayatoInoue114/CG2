#include "MT.h"
#include <algorithm>
#include <cassert>
#include "../MathOperator/MathOperator.h"


Matrix4x4 MakeIdentity4x4() {
	Matrix4x4 mat = {
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};
	return mat;
}

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 resultMatrix = {};

	resultMatrix.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0];
	resultMatrix.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1];
	resultMatrix.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2];
	resultMatrix.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3];

	resultMatrix.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0];
	resultMatrix.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1];
	resultMatrix.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2];
	resultMatrix.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3];

	resultMatrix.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0];
	resultMatrix.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1];
	resultMatrix.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2];
	resultMatrix.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3];

	resultMatrix.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0];
	resultMatrix.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1];
	resultMatrix.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2];
	resultMatrix.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3];

	return resultMatrix;
}

Vector3 Multiply(const Vector3& v, const Matrix4x4& m)
{
	// Vector3を4x1の行列に変換する
	Vector4 v4 = { v.x, v.y, v.z, 1 };

	// Matrix4x4とVector4の行列の積を計算する
	Vector4 result = {
		m.m[0][0] * v4.x + m.m[0][1] * v4.y + m.m[0][2] * v4.z + m.m[0][3] * v4.z,
		m.m[1][0] * v4.x + m.m[1][1] * v4.y + m.m[1][2] * v4.z + m.m[1][3] * v4.z,
		m.m[2][0] * v4.x + m.m[2][1] * v4.y + m.m[2][2] * v4.z + m.m[2][3] * v4.z,
		m.m[3][0] * v4.x + m.m[3][1] * v4.y + m.m[3][2] * v4.z + m.m[3][3] * v4.z
	};

    // 結果のVector4をVector3に変換して返す
	return Vector3(result.x, result.y, result.z);
}

Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 mat = {
		1,0,0,0,
		0,std::cosf(radian),std::sinf(radian),0,
		0,-std::sinf(radian),std::cosf(radian),0,
		0,0,0,1
	};
	return mat;
}

Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 mat = {
		std::cosf(radian),0,-std::sinf(radian),0,
		0,1,0,0,
		std::sinf(radian),0,std::cosf(radian),0,
		0,0,0,1
	};
	return mat;
}

Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 mat = {
		std::cosf(radian),std::sinf(radian),0,0,
		-std::sinf(radian),std::cosf(radian),0,0,
		0,0,1,0,
		0,0,0,1
	};
	return mat;
}

Matrix4x4 MakeRotateXYZMatrix(const Vector3& rotate)
{
	Matrix4x4 x = MakeRotateXMatrix(rotate.x);
	Matrix4x4 y = MakeRotateYMatrix(rotate.y);
	Matrix4x4 z = MakeRotateZMatrix(rotate.z);
	return x * y * z;
}

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
	Matrix4x4 rotateMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));

	Matrix4x4 mat = {
		scale.x * rotateMatrix.m[0][0],   scale.x * rotateMatrix.m[0][1],   scale.x * rotateMatrix.m[0][2],   0,
		scale.y * rotateMatrix.m[1][0],   scale.y * rotateMatrix.m[1][1],   scale.y * rotateMatrix.m[1][2],   0,
		scale.z * rotateMatrix.m[2][0],   scale.z * rotateMatrix.m[2][1],   scale.z * rotateMatrix.m[2][2],   0,
		translate.x,translate.y,translate.z,1
	};
	return mat;
}

//Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Quaternion& rotate, const Vector3& translate) {
//
//	Matrix4x4 rotateMatrix = MakeRotateMatrix(rotate);
//
//	Matrix4x4 mat = {
//		scale.x * rotateMatrix.m[0][0],   scale.x * rotateMatrix.m[0][1],   scale.x * rotateMatrix.m[0][2],   0,
//		scale.y * rotateMatrix.m[1][0],   scale.y * rotateMatrix.m[1][1],   scale.y * rotateMatrix.m[1][2],   0,
//		scale.z * rotateMatrix.m[2][0],   scale.z * rotateMatrix.m[2][1],   scale.z * rotateMatrix.m[2][2],   0,
//		translate.x,translate.y,translate.z,1
//	};
//
//	return mat;
//
//}

float InverseNum(const Matrix4x4& m, int a, int b, int c, int d, int e, int f, int g, int h) {
	float resultNum;
	resultNum = m.m[a - 1][b - 1] * m.m[c - 1][d - 1] * m.m[e - 1][f - 1] * m.m[g - 1][h - 1];
	return resultNum;
}
float InverseNum2(const Matrix4x4& m, int a, int b, int c, int d, int e, int f) {
	float resultNum;
	resultNum = m.m[a - 1][b - 1] * m.m[c - 1][d - 1] * m.m[e - 1][f - 1];
	return resultNum;
}

Matrix4x4 Inverse(const Matrix4x4& m) {
	Matrix4x4 result{};

	float as =
		m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3] +
		m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1] +
		m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2] -

		m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1] -
		m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3] -
		m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2] -

		m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3] -
		m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1] -
		m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2] +

		m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1] +
		m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3] +
		m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2] +

		m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3] +
		m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1] +
		m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2] -

		m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1] -
		m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3] -
		m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2] -

		m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0] -
		m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0] -
		m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0] +

		m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0] +
		m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0] +
		m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0];

	assert(as != 0.0f);
	float determinantRecp = 1.0f / as;

	// 一行目
	result.m[0][0] = (m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] +
		m.m[1][3] * m.m[2][1] * m.m[3][2] - m.m[1][3] * m.m[2][2] * m.m[3][1] -
		m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][2]) *
		determinantRecp;

	result.m[0][1] = (-m.m[0][1] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[2][3] * m.m[3][1] -
		m.m[0][3] * m.m[2][1] * m.m[3][2] + m.m[0][3] * m.m[2][2] * m.m[3][1] +
		m.m[0][2] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][2]) *
		determinantRecp;

	result.m[0][2] = (
		m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][1] +
		m.m[0][3] * m.m[1][1] * m.m[3][2] - m.m[0][3] * m.m[1][2] * m.m[3][1] -
		m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[3][2]) *
		determinantRecp;

	result.m[0][3] = (-m.m[0][1] * m.m[1][2] * m.m[2][3] - m.m[0][2] * m.m[1][3] * m.m[2][1] -
		m.m[0][3] * m.m[1][1] * m.m[2][2] + m.m[0][3] * m.m[1][2] * m.m[2][1] +
		m.m[0][2] * m.m[1][1] * m.m[2][3] + m.m[0][1] * m.m[1][3] * m.m[2][2]) *
		determinantRecp;


	// 二行目
	result.m[1][0] = (-m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[1][2] * m.m[2][3] * m.m[3][0] -
		m.m[1][3] * m.m[2][0] * m.m[3][2] + m.m[1][3] * m.m[2][2] * m.m[3][0] +
		m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[1][0] * m.m[2][3] * m.m[3][2]) *
		determinantRecp;

	result.m[1][1] = (
		m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][0] +
		m.m[0][3] * m.m[2][0] * m.m[3][2] - m.m[0][3] * m.m[2][2] * m.m[3][0] -
		m.m[0][2] * m.m[2][0] * m.m[3][3] - m.m[0][0] * m.m[2][3] * m.m[3][2]) *
		determinantRecp;

	result.m[1][2] = (-m.m[0][0] * m.m[1][2] * m.m[3][3] - m.m[0][2] * m.m[1][3] * m.m[3][0] -
		m.m[0][3] * m.m[1][0] * m.m[3][2] + m.m[0][3] * m.m[1][2] * m.m[3][0] +
		m.m[0][2] * m.m[1][0] * m.m[3][3] + m.m[0][0] * m.m[1][3] * m.m[3][2]) *
		determinantRecp;

	result.m[1][3] = (
		m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] +
		m.m[0][3] * m.m[1][0] * m.m[2][2] - m.m[0][3] * m.m[1][2] * m.m[2][0] -
		m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][0] * m.m[1][3] * m.m[2][2]) *
		determinantRecp;


	// 三行目
	result.m[2][0] = (
		m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] +
		m.m[1][3] * m.m[2][0] * m.m[3][1] - m.m[1][3] * m.m[2][1] * m.m[3][0] -
		m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][0] * m.m[2][3] * m.m[3][1]) *
		determinantRecp;

	result.m[2][1] = (-m.m[0][0] * m.m[2][1] * m.m[3][3] - m.m[0][1] * m.m[2][3] * m.m[3][0] -
		m.m[0][3] * m.m[2][0] * m.m[3][1] + m.m[0][3] * m.m[2][1] * m.m[3][0] +
		m.m[0][1] * m.m[2][0] * m.m[3][3] + m.m[0][0] * m.m[2][3] * m.m[3][1]) *
		determinantRecp;

	result.m[2][2] = (
		m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] +
		m.m[0][3] * m.m[1][0] * m.m[3][1] - m.m[0][3] * m.m[1][1] * m.m[3][0] -
		m.m[0][1] * m.m[1][0] * m.m[3][3] - m.m[0][0] * m.m[1][3] * m.m[3][1]) *
		determinantRecp;

	result.m[2][3] = (-m.m[0][0] * m.m[1][1] * m.m[2][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] -
		m.m[0][3] * m.m[1][0] * m.m[2][1] + m.m[0][3] * m.m[1][1] * m.m[2][0] +
		m.m[0][1] * m.m[1][0] * m.m[2][3] + m.m[0][0] * m.m[1][3] * m.m[2][1]) *
		determinantRecp;


	// 四行目
	result.m[3][0] = (-m.m[1][0] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][2] * m.m[3][0] -
		m.m[1][2] * m.m[2][0] * m.m[3][1] + m.m[1][2] * m.m[2][1] * m.m[3][0] +
		m.m[1][1] * m.m[2][0] * m.m[3][2] + m.m[1][0] * m.m[2][2] * m.m[3][1]) *
		determinantRecp;

	result.m[3][1] = (

		m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] +
		m.m[0][2] * m.m[2][0] * m.m[3][1] - m.m[0][2] * m.m[2][1] * m.m[3][0] -
		m.m[0][1] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][2] * m.m[3][1]) *
		determinantRecp;

	result.m[3][2] = (-m.m[0][0] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][2] * m.m[3][0] -
		m.m[0][2] * m.m[1][0] * m.m[3][1] + m.m[0][2] * m.m[1][1] * m.m[3][0] +
		m.m[0][1] * m.m[1][0] * m.m[3][2] + m.m[0][0] * m.m[1][2] * m.m[3][1]) *
		determinantRecp;

	result.m[3][3] = (

		m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] +
		m.m[0][2] * m.m[1][0] * m.m[2][1] - m.m[0][2] * m.m[1][1] * m.m[2][0] -
		m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][2] * m.m[2][1]) *
		determinantRecp;

	return result;
}

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
	Matrix4x4 result{};

	result.m[0][0] = (1 / aspectRatio) * 1 / std::tan(fovY / 2);
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1 / std::tan(fovY / 2);
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = farClip / (farClip - nearClip);
	result.m[2][3] = 1.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = -nearClip * farClip / (farClip - nearClip);
	result.m[3][3] = 0.0f;

	return result;
}
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {
	Matrix4x4 mat = {
		2 / (right - left),	0,0,0,
		0,2 / (top - bottom),0,0,
		0,0,1 / (farClip - nearClip),0,
		(left + right) / (left - right),(top + bottom) / (bottom - top),nearClip / (nearClip - farClip),1
	};
	return mat;
}

Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 mat = {
		width / 2,0,0,0,
		0,-height / 2,0,0,
		0,0,maxDepth - minDepth,0,
		left + width / 2,top + height / 2,minDepth,1
	};
	return mat;
}

Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
	Matrix4x4 result{};
	result.m[0][0] = scale.x;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = scale.y;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = scale.z;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;
	return result;
}

Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {
	Matrix4x4 result{};
	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;
	result.m[2][3] = 0.0f;

	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	result.m[3][3] = 1.0f;
	return result;
}

//正規化
Vector3 Normalize(const Vector3& v) {
	Vector3 result{};
	float norm = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	result.x = v.x / norm;
	result.y = v.y / norm;
	result.z = v.z / norm;
	return result;
}

//Vector3型の和
Vector3 Add(const Vector3& v1, const Vector3& v2) {
	Vector3 num = { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
	return num;
}

Vector2 Add(const Vector2& v1, const Vector2& v2) {
	Vector2 num = { v1.x + v2.x, v1.y + v2.y };
	return num;
}

//長さ
float Length(const Vector3& v) {
	float num = { sqrtf(v.x * v.x + v.y * v.y + v.z * v.z) };
	return num;
}

//内積
float Dot(const Vector3& v1, const Vector3& v2) {
	float num = { v1.x * v2.x + v1.y * v2.y + v1.z * v2.z };
	return num;
}

//球面線形補間
Vector3 Slerp(const Vector3& v1, const Vector3& v2, float t) {
	float dot = Dot(v1, v2);

	t = std::clamp(t, 0.0f, 1.0f);

	float theta = std::acosf(dot) * t;

	Vector3 intermediate = { v2.x - v1.x * dot, v2.y - v1.y * dot, v2.z - v1.z * dot };

	float s = std::sinf(theta);

	return {
		v1.x * std::cosf(theta) + intermediate.x * s,
		v1.y * std::cosf(theta) + intermediate.y * s,
		v1.z * std::cosf(theta) + intermediate.z * s,
	};
}

//減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 num = { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
	return num;
}

Vector2 Subtract(const Vector2& v1, const Vector2& v2) {
	Vector2 num = { v1.x - v2.x, v1.y - v2.y };
	return num;
}

//スカラー倍
Vector3 Multiply(const Vector3& v, float scalar) {
	Vector3 num = { scalar * v.x, scalar * v.y, scalar * v.z };
	return num;
}

//正面へのベクトルを取得
Vector3 ForwardVector(const Vector3& rotate) {
	// ローカルZ軸の方向ベクトルを取得
	Vector3 forwardVector = {
		std::sin(rotate.y),
		0,
		std::cos(rotate.y)
	};

	forwardVector = Normalize(forwardVector);

	return forwardVector;
}

//線形補間
float Lerp(float a, float b, float t) {
	return a * (1.0f - t) + b * t;
}

//線形補間
Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t) {
	return Vector3(
		Lerp(v1.x, v2.x, t),
		Lerp(v1.y, v2.y, t),
		Lerp(v1.z, v2.z, t)
	);
}

//AABBの当たり判定
bool IsCollision(const AABB& aabb1, const AABB& aabb2) {
	if ((aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) &&
		(aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) &&
		(aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z)
		) {
		return true;
	}
	return false;
}

//AABBを作る
AABB CreateAABB(const Vector3& scale, const Vector3& translate) {
	Vector3 min = Divide(Multiply(scale, -1.0f), 2.0f);
	Vector3 max = Divide(Multiply(scale, 1.0f), 2.0f);

	min = Add(min, translate);
	max = Add(max, translate);

	AABB result = { min,max };

	return result;
}

//ベクトルの除算
Vector3 Divide(const Vector3& v, float scalar) {
	return { v.x / scalar, v.y / scalar, v.z / scalar };
}

// 線分とAABBの当たり判定
bool IsCollision(const AABB& box, const LineSegment& line) {
	Vector3 dir = Subtract(line.end, line.start);

	if (std::abs(dir.x) < 0.001f) {
		if (line.start.x < box.min.x || line.start.x > box.max.x) {
			return false;
		}
	}
	else {
		float invDir = 1.0f / dir.x;
		float t1 = (box.min.x - line.start.x) * invDir;
		float t2 = (box.max.x - line.start.x) * invDir;

		float tMin = std::min(t1, t2);
		float tMax = std::max(t1, t2);

		if (tMin > 1.0f || tMax < 0.0f) {
			return false;
		}
	}

	if (std::abs(dir.y) < 0.001f) {
		if (line.start.y < box.min.y || line.start.y > box.max.y) {
			return false;
		}
	}
	else {
		float invDir = 1.0f / dir.y;
		float t1 = (box.min.y - line.start.y) * invDir;
		float t2 = (box.max.y - line.start.y) * invDir;

		float tMin = std::min(t1, t2);
		float tMax = std::max(t1, t2);

		if (tMin > 1.0f || tMax < 0.0f) {
			return false;
		}
	}

	if (std::abs(dir.z) < 0.001f) {
		if (line.start.z < box.min.z || line.start.z > box.max.z) {
			return false;
		}
	}
	else {
		float invDir = 1.0f / dir.z;
		float t1 = (box.min.z - line.start.z) * invDir;
		float t2 = (box.max.z - line.start.z) * invDir;

		float tMin = std::min(t1, t2);
		float tMax = std::max(t1, t2);

		if (tMin > 1.0f || tMax < 0.0f) {
			return false;
		}
	}

	return true;
}

//bool IsCollision(const AABB& aabb, const Segment& segment) {
//	// それぞれの媒介変数を求める
//	float tMinX = (aabb.min.x - segment.origin.x) / segment.diff.x;
//	float tMaxX = (aabb.max.x - segment.origin.x) / segment.diff.x;
//	float tMinY = (aabb.min.y - segment.origin.y) / segment.diff.y;
//	float tMaxY = (aabb.max.y - segment.origin.y) / segment.diff.y;
//	float tMinZ = (aabb.min.z - segment.origin.z) / segment.diff.z;
//	float tMaxZ = (aabb.max.z - segment.origin.z) / segment.diff.z;
//
//	// 衝突点の近い方と遠い方を求める
//	float tNearX = std::min(tMinX, tMaxX);
//	float tFarX = std::max(tMinX, tMaxX);
//	float tNearY = std::min(tMinY, tMaxY);
//	float tFarY = std::max(tMinY, tMaxY);
//	float tNearZ = std::min(tMinZ, tMaxZ);
//	float tFarZ = std::max(tMinZ, tMaxZ);
//
//	// AABBとの衝突点(貫通点)のtが小さい方
//	float tMin = std::max(std::max(tNearX, tNearY), tNearZ);
//	// AABBとの衝突点(貫通点)のtが大きい方
//	float tMax = std::min(std::min(tFarX, tFarY), tFarZ);
//
//	// 衝突しているかどうか判定
//	if (tMin <= tMax && ((tMin >= 0.0f && tMin <= 1.0f) || (tMax >= 0.0f && tMax <= 1.0f))) {
//		return true;
//	}
//
//	return false;
//}



int Min(int num1, int num2) {
	if (num1 < num2) {
		return num1;
	}
	else {
		return num2;
	}
}

float Min(float num1, float num2) {
	if (num1 < num2) {
		return num1;
	}
	else {
		return num2;
	}
}

int Max(int num1, int num2) {
	if (num1 > num2) {
		return num1;
	}
	else {
		return num2;
	}
}

float Max(float num1, float num2) {
	if (num1 > num2) {
		return num1;
	}
	else {
		return num2;
	}
}

//Vector2 operator+(const Vector2& a, const Vector2& b) {
//	Vector2 c = { a.x + b.x,a.y + b.y };
//
//	return c;
//}
//
//Vector2 operator-(const Vector2& a, const Vector2& b) {
//	Vector2 c = { a.x - b.x,a.y - b.y };
//
//	return c;
//}
//
//Vector2 operator*(const Vector2& a, const Vector2& b) {
//	Vector2 c = { a.x * b.x,a.y * b.y };
//
//	return c;
//}
//
//Vector2 operator*(const float& a, const Vector2& b) {
//	Vector2 c = { a * b.x,a * b.y };
//
//	return c;
//}
//
//Vector3 operator+(const Vector3& a, const Vector3& b) {
//	Vector3 c = { a.x + b.x,a.y + b.y ,a.z + b.z };
//
//	return c;
//}
//
//Vector3 operator+(const Vector3& a, const float& b) {
//	Vector3 c = { a.x + b,a.y + b,a.z + b };
//
//	return c;
//}
//
//Vector3 operator-(const Vector3& a, const Vector3& b) {
//	Vector3 c = { a.x - b.x,a.y - b.y,a.z - b.z };
//
//	return c;
//}
//
//Vector3 operator-(const Vector3& a, const float& b) {
//	Vector3 c = { a.x - b,a.y - b,a.z - b };
//
//	return c;
//}
//
//Vector3 operator*(const Vector3& a, const Vector3& b) {
//	Vector3 c = { a.x * b.x, a.y * b.y, a.z * b.z };
//
//	return c;
//}
//
//Vector3 operator*(const float& a, const Vector3& b) {
//	Vector3 c = { a * b.x,a * b.y,a * b.z };
//
//	return c;
//}
//
//// Vector3とMatrix4x4の乗算関数
//Vector3 operator*(const Vector3& vec, const Matrix4x4& mat) {
//	Vector4 result = {
//		vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + vec.z * mat.m[2][0] + mat.m[3][0],
//		vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + vec.z * mat.m[2][1] + mat.m[3][1],
//		vec.x * mat.m[0][2] + vec.y * mat.m[1][2] + vec.z * mat.m[2][2] + mat.m[3][2],
//		vec.x * mat.m[0][3] + vec.y * mat.m[1][3] + vec.z * mat.m[2][3] + mat.m[3][3]
//	};
//
//	// 4次元ベクトルを3次元ベクトルに戻す
//	return { result.x / result.w, result.y / result.w, result.z / result.w };
//}

Matrix4x4 Transpose(const Matrix4x4& m) {
	Matrix4x4 mat = { m.m[0][0], m.m[1][0], m.m[2][0], m.m[3][0], m.m[0][1], m.m[1][1],
					 m.m[2][1], m.m[3][1], m.m[0][2], m.m[1][2], m.m[2][2], m.m[3][2],
					 m.m[0][3], m.m[0][3], m.m[2][3], m.m[3][3] };
	return mat;
}

Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m) {
	Vector3 result{
		v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
		v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
		v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] };
	return result;
}

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result = {};
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] +
		1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] +
		1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] +
		1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] +
		1.0f * matrix.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;
	return result;
}

// CatmullRom補間
Vector3 CatmullRomInterpolation(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3& p3, float t) {

	//float s = 0.5f;
	//float t2 = t * t;
	//float t3 = t * t * t;
	//Vector3 hr1 = (-p0 + (3.0f * p1) - (3.0f * p2) + p3) * t3;
	//Vector3 hr2 = ((2.0f * p0) - (5.0f * p1) + (4.0f * p2) - p3) * t2;
	//Vector3 hr3 = ((-p0 + p2) * t) + (2.0f + p1);
	//return (s * (hr1 + hr2 + hr3));

	float t2 = t * t;
	float t3 = t * t * t;
	return Vector3(
		//x
		0.5f * ((-p0.x + 3 * p1.x - 3 * p2.x + p3.x) * t3 +
			(2 * p0.x - 5 * p1.x + 4 * p2.x - p3.x) * t2 + (-p0.x + p2.x) * t + 2 * p1.x),
		//y
		0.5f * ((-p0.y + 3 * p1.y - 3 * p2.y + p3.y) * t3 +
			(2 * p0.y - 5 * p1.y + 4 * p2.y - p3.y) * t2 + (-p0.y + p2.y) * t + 2 * p1.y),
		//z
		0.5f * ((-p0.z + 3 * p1.z - 3 * p2.z + p3.z) * t3 +
			(2 * p0.z - 5 * p1.z + 4 * p2.z - p3.z) * t2 + (-p0.z + p2.z) * t + 2 * p1.z)
	);
}

// CatmullRomスプライン曲線上の座標を得る
Vector3 CatmullRomPosition(const std::vector<Vector3>& points, uint32_t index, float t) {

	const uint32_t kIndex = uint32_t(points.size() - 1);

	int index0 = ((index - 1) + kIndex) % kIndex;
	int index1 = index;
	int index2 = (index + 1) % kIndex;
	int index3 = (index + 2) % kIndex;

	Vector3 p0 = points[index0];
	Vector3 p1 = points[index1];
	Vector3 p2 = points[index2];
	Vector3 p3 = points[index3];

	return CatmullRomInterpolation(p0, p1, p2, p3, t);
}

Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs) {
	float w = lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z;
	float x = lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y;
	float y = lhs.w * rhs.y - lhs.x * rhs.z + lhs.y * rhs.w + lhs.z * rhs.x;
	float z = lhs.w * rhs.z + lhs.x * rhs.y - lhs.y * rhs.x + lhs.z * rhs.w;

	return Quaternion(x, y, z, w);
}

Quaternion IdentityQuaternion() {
	return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
}

Quaternion Conjugete(const Quaternion& quaternion) {
	return Quaternion(-quaternion.x, -quaternion.y, -quaternion.z, quaternion.w);
}

float Norm(const Quaternion& v) {
	float result{};
	result = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
	return result;
}

Quaternion Normalize(const Quaternion& quaternion) {
	if (Norm(quaternion) != 0.0f) {
		//float invNorm = 1.0f / Norm(quaternion);
		Quaternion num = {
			quaternion.x / Norm(quaternion),
			quaternion.y / Norm(quaternion),
			quaternion.z / Norm(quaternion),
			quaternion.w / Norm(quaternion)
		};
		return num;
	}

	return quaternion;
}

Quaternion Inverse(const Quaternion& v) {
	float norm = Norm(v) * Norm(v);
	Quaternion con = Conjugete(v);
	Quaternion result = {
		con.x / norm,
		con.y / norm,
		con.z / norm,
		con.w / norm
	};

	return result;
}

Quaternion MakeRotateAxisAngleQuaternion(const Vector3& axis, float angle) {
	float halfAngle = angle * 0.5f;

	float axisLength = sqrt(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
	float sinHalfAngle = sin(halfAngle);
	Vector3 normalizedAxis = { axis.x / axisLength, axis.y / axisLength, axis.z / axisLength };

	Quaternion result{};
	result.w = cos(halfAngle);
	result.x = normalizedAxis.x * sinHalfAngle;
	result.y = normalizedAxis.y * sinHalfAngle;
	result.z = normalizedAxis.z * sinHalfAngle;

	return result;
}

Vector3 RotateVector(const Vector3& vector, const Quaternion& quaternion) {
	// クォータニオンの逆元を計算
	Quaternion conjugate = { quaternion.w, -quaternion.x, -quaternion.y, -quaternion.z };
	float normSquared = quaternion.w * quaternion.w + quaternion.x * quaternion.x + quaternion.y * quaternion.y + quaternion.z * quaternion.z;

	// 回転したベクトルを求める
	Quaternion vQuat = { 1.0f, vector.x, vector.y, vector.z };
	Quaternion rotated = Multiply(conjugate, Multiply(quaternion, vQuat));

	// ノルムの二乗で逆元を掛ける
	rotated = { rotated.x / normSquared, rotated.y / normSquared, rotated.z / normSquared, rotated.w / normSquared };

	return { rotated.x, rotated.y, rotated.z };
}

Matrix4x4 MakeRotateMatrix(const Quaternion& q) {
	Matrix4x4 result = {
		q.w * q.w + q.x * q.x - q.y * q.y - q.z * q.z,  2 * (q.x * q.y + q.w * q.z),  2 * (q.x * q.z - q.w * q.y),0,
		2 * (q.x * q.y - q.w * q.z),  q.w * q.w - q.x * q.x + q.y * q.y - q.z * q.z,  2 * (q.y * q.z + q.w * q.x),0,
		2 * (q.x * q.z + q.w * q.y), 2 * (q.y * q.z - q.w * q.x),q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z,0,
		0,0,0,1
	};

	return result;
}

// 内積
float Dot(const Quaternion& q1, const Quaternion& q2) {
	return (q1.x * q2.x) + (q1.y * q2.y) + (q1.z * q2.z) + (q1.w * q2.w);
}

// 球面線形補間
Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float t) {
	Quaternion q = q0;
	float dot = Dot(q0, q1);
	if (dot < 0.0f) {
		q = -q;
		dot = -dot;
	}
	constexpr float EPSILON = 0.0001f;
	if (dot >= 1.0f - EPSILON) {
		return (1.0f - t) * q + t * q0;
	}
	float theta = std::acos(dot);
	float sinTheta = 1.0f / std::sin(theta);
	float scale1 = std::sin((1.0f - t) * theta) * sinTheta;
	float scale2 = std::sin(t * theta) * sinTheta;
	return (q * scale1) + (q1 * scale2);
}

Quaternion ConvertFromRotateMatrix(const Matrix4x4& matrix) {

	Quaternion qr = IdentityQuaternion();

	float elem[4]{}; //0:x 1:y 2:z 3:w

	elem[0] = matrix.m[0][0] - matrix.m[1][1] - matrix.m[2][2] + 1.0f;
	elem[1] = -matrix.m[0][0] + matrix.m[1][1] - matrix.m[2][2] + 1.0f;
	elem[2] = -matrix.m[0][0] - matrix.m[1][1] + matrix.m[2][2] + 1.0f;
	elem[3] = matrix.m[0][0] + matrix.m[1][1] + matrix.m[2][2] + 1.0f;

	//最大成分のインデックス
	uint32_t biggestIndex = 0;
	for (uint32_t i = 0; i < 4; i++) {
		if (elem[i] > elem[biggestIndex]) {
			biggestIndex = i;
		}
	}

	float tmpQr[4]{}; //仮クォータニオン
	float v = std::sqrtf(elem[biggestIndex]) * 0.5f;

	tmpQr[biggestIndex] = v;

	float multi = 0.25f / v;

	switch (biggestIndex)
	{
	default:
	case 0:
		tmpQr[1] = (matrix.m[0][1] + matrix.m[1][0]) * multi;
		tmpQr[2] = (matrix.m[2][0] + matrix.m[0][2]) * multi;
		tmpQr[3] = (matrix.m[1][2] - matrix.m[2][1]) * multi;
		break;
	case 1:
		tmpQr[0] = (matrix.m[0][1] + matrix.m[1][0]) * multi;
		tmpQr[2] = (matrix.m[1][2] + matrix.m[2][1]) * multi;
		tmpQr[3] = (matrix.m[2][0] - matrix.m[0][2]) * multi;
		break;
	case 2:
		tmpQr[0] = (matrix.m[2][0] + matrix.m[0][2]) * multi;
		tmpQr[1] = (matrix.m[1][2] + matrix.m[2][1]) * multi;
		tmpQr[3] = (matrix.m[0][1] - matrix.m[1][0]) * multi;
		break;
	case 3:
		tmpQr[0] = (matrix.m[1][2] - matrix.m[2][1]) * multi;
		tmpQr[1] = (matrix.m[2][0] - matrix.m[0][2]) * multi;
		tmpQr[2] = (matrix.m[0][1] - matrix.m[1][0]) * multi;
		break;
	}

	qr.x = tmpQr[0];
	qr.y = tmpQr[1];
	qr.z = tmpQr[2];
	qr.w = tmpQr[3];

	return qr;

}

// 3次元アフィン変換行列 (W = SRT)
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Quaternion& rotate, const Vector3& translate) {
	Matrix4x4 result{};

	// 拡大縮小行列
	Matrix4x4 scaleMatrix;
	scaleMatrix = MakeScaleMatrix(scale);

	// 回転行列(all)
	Matrix4x4 rotateMatrix;
	rotateMatrix = MakeRotateMatrix(rotate);

	// 平行移動行列
	Matrix4x4 translateMatrix;
	translateMatrix = MakeTranslateMatrix(translate);

	result = scaleMatrix * (rotateMatrix * translateMatrix);

	return result;
}

Vector3 GetFrontVector(Vector3 rotate) {
	Matrix4x4 wM = MakeRotateXYZMatrix(rotate);
	Vector3 dir = { 0.0f,0.0f,1.0f };
	return Normalize(Multiply(dir, wM));
}

//Vector3 GetRotateForVector(Vector3 vector) {
//	// Y軸周り角度(0y)
//	worldTransform_.rotate.y = std::atan2(velocity_.x, velocity_.z);
//
//	velocityXZ_ = std::sqrt(velocity_.x * velocity_.x + velocity_.z * velocity_.z);
//	// X軸周り角度(0x)
//	worldTransform_.rotate.x = std::atan2(-velocity_.y, velocityXZ_);
//}