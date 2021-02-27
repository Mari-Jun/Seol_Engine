#include "stdafx.h"
#include "PARS/Math/MathFunc.h"
#include "PARS/Math/Vec3.h"
#include "PARS/Math/Mat4.h"
#include "PARS/Math/Quaternion.h"

namespace PARS
{
	Mat4::Mat4()
	{
		*this = Mat4::Identity;
	}

	Mat4::Mat4(float* mat)
	{
		memcpy(this->mat, mat, 16 * sizeof(float));
	}

	Mat4::Mat4(float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44)
	{
		mat[0][0] = m11,	mat[0][1] = m12,	mat[0][2] = m13,	mat[0][3] = m14;
		mat[1][0] = m21,	mat[1][1] = m22,	mat[1][2] = m23,	mat[1][3] = m24;
		mat[2][0] = m31,	mat[2][1] = m32,	mat[2][2] = m33,	mat[2][3] = m34;
		mat[3][0] = m41,	mat[3][1] = m42,	mat[3][2] = m43,	mat[3][3] = m44;
	}

	Mat4 operator*(const Mat4& lhs, const Mat4& rhs)
	{
		Mat4 result;

		for (auto row = 0; row < 4; ++row)
		{
			for (auto col = 0; col < 4; col++)
			{
				float sum = 0.0f;
				for (auto i = 0; i < 4; i++)
				{
					sum += lhs.mat[row][i] * rhs.mat[i][col];
				}
				result.mat[row][col] = sum;
			}
		}

		return result;
	}

	Mat4& Mat4::operator*=(const Mat4& mat)
	{
		*this = *this * mat;
		return *this;
	}

	std::ostream& operator<<(std::ostream& os, const Mat4& mat)
	{
		return os << mat.ToString();
	}

	void Mat4::Invert()
	{
		XMMATRIX temp = ConvertToXMMATRIX();
		temp = XMMatrixInverse(nullptr, temp);
		ConvertFromXMMATRIX(temp);
	}

	Vec3 Mat4::GetTranslation() const
	{
		return Vec3(mat[3][0], mat[3][1], mat[3][2]);
	}

	Mat4 Mat4::CreateScale(float x, float y, float z)
	{
		return Mat4(
			x, 0.0f, 0.0f, 0.0f,
			0.0f, y, 0.0f, 0.0f,
			0.0f, 0.0f, z, 0.0f,
			0.0f, 0.0f, 0.0, 1.0f
		);
	}

	Mat4 Mat4::CreateScale(float scale)
	{
		return Mat4::CreateScale(scale, scale, scale);
	}

	Mat4 Mat4::CreateScale(const Vec3& vec)
	{
		return Mat4::CreateScale(vec.x, vec.y, vec.z);
	}

	Mat4 Mat4::CreateRotationX(float angle)
	{
		float r = Math::ToRadians(angle);
		return Mat4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, Math::Cos(r), Math::Sin(r), 0.0f, 
			0.0f, -Math::Sin(r), Math::Cos(r), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	Mat4 Mat4::CreateRotationY(float angle)
	{
		float r = Math::ToRadians(angle);
		return Mat4(
			Math::Cos(r), 0.0f, -Math::Sin(r), 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			Math::Sin(r), 0.0f, Math::Cos(r), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	Mat4 Mat4::CreateRotationZ(float angle)
	{
		float r = Math::ToRadians(angle);
		return Mat4(
			Math::Cos(r), Math::Sin(r), 0.0f, 0.0f,
			-Math::Sin(r), Math::Cos(r), 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	Mat4 Mat4::CreateRotationFromQuaternion(const Quaternion& q)
	{
		Mat4 result;
		result.mat[0][0] = 1.0f - 2.0f * (q.y * q.y + q.z * q.z);
		result.mat[0][1] = 2.0f * (q.x * q.y + q.w * q.z);
		result.mat[0][2] = 2.0f * (q.x * q.z - q.w * q.y);
		result.mat[0][3] = 0.0f;

		result.mat[1][0] = 2.0f * (q.x * q.y - q.w * q.z);
		result.mat[1][1] = 1.0f - 2.0f * (q.x * q.x + q.z * q.z);
		result.mat[1][2] = 2.0f * (q.y * q.z + q.w * q.x);
		result.mat[1][3] = 0.0f;

		result.mat[2][0] = 2.0f * (q.x * q.z + q.w * q.y);
		result.mat[2][1] = 2.0f * (q.y * q.z - q.w * q.x);
		result.mat[2][2] = 1.0f - 2.0f * (q.x * q.x + q.y * q.y);
		result.mat[2][3] = 0.0f;

		result.mat[3][0] = 0.0f;
		result.mat[3][1] = 0.0f;
		result.mat[3][2] = 0.0f;
		result.mat[3][3] = 1.0f;

		return result;
	}

	Mat4 Mat4::CreateTranslation(float x, float y, float z)
	{
		return Mat4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			x, y, z, 1.0f
		);
	}

	Mat4 Mat4::CreateTranslation(const Vec3& vec)
	{
		return Mat4::CreateTranslation(vec.x, vec.y, vec.z);
	}

	Mat4 Mat4::LookAt(const Vec3& eye, const Vec3& target, const Vec3& up)
	{
		Vec3 n = Vec3::Normalize(target - eye);
		Vec3 u = Vec3::Cross(up, n);
		Vec3 v = Vec3::Cross(n, u);
		Vec3 trans;
		trans.x = -Vec3::Dot(u, eye);
		trans.y = -Vec3::Dot(v, eye);
		trans.z = -Vec3::Dot(n, eye);

		Mat4 result(
			u.x, v.x, n.x, 0.0f,
			u.y, v.y, n.y, 0.0f,
			u.z, v.z, n.z, 0.0f,
			trans.x, trans.y, trans.z, 1.0f
		);

		return result;
	}

	Mat4 Mat4::Ortho(float left, float right, float bottom, float top, float near, float far)
	{
		return Mat4(
			2.0f / (right - left), 0.0f, 0.0f, 0.0f,
			0.0f, 2.0f / (top - bottom), 0.0f, 0.0f,
			0.0f, 0.0f, 2.0f / (near - far), 0.0f,
			(left + right) / (left - right), (bottom + top) / (bottom - top), (far + near) / (far - near), 1.0f
		);
	}

	Mat4 Mat4::Perspective(float fovy, float aspect, float near, float far)
	{
		float yScale = Math::Cot(fovy / 2.0f);
		float xScale = yScale / aspect;
		float fRange = far / (far - near);

		return Mat4(
			xScale, 0.0f, 0.0f, 0.0f,
			0.0f, yScale, 0.0f, 0.0f,
			0.0f, 0.0f, fRange, 1.0f,
			0.0f, 0.0f, -fRange * near, 0.0f
		);
	}

	void Mat4::Transpose()
	{
		Mat4 temp = *this;
		for (auto row = 0; row < 4; ++row)
		{
			for (auto col = 0; col < 4; col++)
			{
				mat[row][col] = temp.mat[col][row];
			}
		}
	}

	Mat4 Mat4::Transpose(const Mat4& mat)
	{
		auto result(mat);
		result.Transpose();
		return result;
	}

	XMMATRIX Mat4::ConvertToXMMATRIX()
	{
		XMFLOAT4X4 temp;
		memcpy(temp.m, mat, 16 * sizeof(float));
		XMMATRIX result = XMLoadFloat4x4(&temp);
		return result;
	}

	void Mat4::ConvertFromXMMATRIX(const XMMATRIX& matrix)
	{
		XMFLOAT4X4 result;
		XMStoreFloat4x4(&result, matrix);
		memcpy(mat, result.m, 16 * sizeof(float));
	}

	std::string Mat4::ToString() const
	{
		std::stringstream result;
		result << "Mat4\n";
		result << "{" << mat[0][0] << ", " << mat[0][1] << ", " << mat[0][2] << ", " << mat[0][3] << "}\n";
		result << "{" << mat[1][0] << ", " << mat[1][1] << ", " << mat[1][2] << ", " << mat[1][3] << "}\n";
		result << "{" << mat[2][0] << ", " << mat[2][1] << ", " << mat[2][2] << ", " << mat[2][3] << "}\n";
		result << "{" << mat[3][0] << ", " << mat[3][1] << ", " << mat[3][2] << ", " << mat[3][3] << "}\n";
		return result.str();
	}
	
	const Mat4 Mat4::Identity{ 
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
	};
}