#include "stdafx.h"
#include "PARS/Math/Vec2.h"
#include "PARS/Math/Mat3.h"

namespace PARS
{
	Mat3::Mat3()
	{
		*this = Mat3::Identity;
	}

	Mat3::Mat3(float* mat)
	{
		memcpy(this->mat, mat, 9 * sizeof(float));
	}

	Mat3::Mat3(float m11, float m12, float m13,
		float m21, float m22, float m23,
		float m31, float m32, float m33)
	{
		mat[0][0] = m11;	mat[0][1] = m12;	mat[0][2] = m13;
		mat[1][0] = m21;	mat[1][1] = m22;	mat[1][2] = m23;
		mat[2][0] = m31;	mat[2][1] = m32;	mat[2][2] = m33;
	}

	Mat3 operator*(const Mat3& lhs, const Mat3& rhs)
	{
		Mat3 result;

		for (auto row = 0; row < 3; ++row)
		{
			for (auto col = 0; col < 3; col++)
			{
				float sum = 0.0f;
				for (auto i = 0; i < 3; i++)
				{
					sum += lhs.mat[row][i] * rhs.mat[i][col];
				}
				result.mat[row][col] = sum;
			}
		}

		return result;
	}

	Mat3& Mat3::operator*=(const Mat3& mat)
	{
		*this = *this * mat;
		return *this;
	}

	std::ostream& operator<<(std::ostream& os, const Mat3& mat)
	{
		return os << mat.ToString();
	}

	Mat3 Mat3::CreateScale(float x, float y)
	{
		return Mat3(
			x, 0.0f, 0.0f,
			0.0f, y, 0.0f,
			0.0f, 0.0f, 1.0f
		);
	}

	Mat3 Mat3::CreateScale(float scale)
	{
		return Mat3::CreateScale(scale, scale);
	}

	Mat3 Mat3::CreateScale(const Vec2& vec)
	{
		return Mat3::CreateScale(vec.x, vec.y);
	}

	Mat3 Mat3::CreateRotation(float angle)
	{
		float r = Math::ToRadians(angle);
		return Mat3(
			Math::Cos(r), Math::Sin(r), 0.0f,
			-Math::Sin(r), Math::Cos(r), 0.0f,
			0.0f, 0.0f, 1.0f
		);
	}

	Mat3 Mat3::CreateTranslation(float x, float y)
	{
		return Mat3(
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			x, y, 1.0f
		);
	}

	Mat3 Mat3::CreateTranslation(const Vec2& vec)
	{
		return Mat3::CreateTranslation(vec.x, vec.y);
	}

	std::string Mat3::ToString() const
	{
		std::stringstream result;
		result << "Mat3\n";
		result << "{" << mat[0][0] << ", " << mat[0][1] << ", " << mat[0][2] << "}\n";
		result << "{" << mat[1][0] << ", " << mat[1][1] << ", " << mat[1][2] << "}\n";
		result << "{" << mat[2][0] << ", " << mat[2][1] << ", " << mat[2][2] << "}\n";
		return result.str();
	}

	const Mat3 Mat3::Identity{ 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
}