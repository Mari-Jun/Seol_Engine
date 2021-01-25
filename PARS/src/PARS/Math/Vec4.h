#pragma once
#include "stdafx.h"

namespace PARS
{
	using Vec4 = XMFLOAT4;

	inline Vec4 operator+=(const Vec4& lhs, const Vec4& rhs)
	{
		return Vec4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
	}

	inline Vec4 operator+(const Vec4& lhs, const Vec4& rhs)
	{
		auto result(lhs);
		result += rhs;
		return result;
	}

	inline Vec4 operator-=(const Vec4& lhs, const Vec4& rhs)
	{
		return Vec4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
	}

	inline Vec4 operator-(const Vec4& lhs, const Vec4& rhs)
	{
		auto result(lhs);
		result -= rhs;
		return result;
	}

	inline Vec4 operator*=(const Vec4& lhs, float scalar)
	{
		return Vec4(lhs.x * scalar, lhs.y * scalar, lhs.z * scalar, lhs.w * scalar);
	}

	inline Vec4 operator*(const Vec4& lhs, float scalar)
	{
		return lhs *= scalar;
	}

	inline Vec4 operator*(float scalar, const Vec4& rhs)
	{
		return rhs *= scalar;
	}

	inline bool operator==(const Vec4& lhs, const Vec4& rhs)
	{
		return Math::NearZero(lhs.x - rhs.x)
			&& Math::NearZero(lhs.y - rhs.y)
			&& Math::NearZero(lhs.z - rhs.z);
	}

	inline bool operator!=(const Vec4& lhs, const Vec4& rhs)
	{
		return !(lhs == rhs);
	}

	namespace VEC4
	{
		static constexpr Vec4 Zero{ 0.0f, 0.0f, 0.0f, 0.0f};	

		inline std::string ToString(const Vec4& vec)
		{
			std::stringstream result;
			result << "Vec4 : {" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << "}";
			return result.str();
		}
	}

	inline std::ostream& operator<<(std::ostream& os, const Vec4& vec)
	{
		return os << VEC4::ToString(vec);
	}

	namespace COLOR
	{
		static constexpr Vec4 Black		{ 0.0f, 0.0f, 0.0f, 1.0f };
		static constexpr Vec4 White		{ 1.0f, 1.0f, 1.0f, 1.0f };
		static constexpr Vec4 Red		{ 1.0f, 0.0f, 0.0f, 1.0f };
		static constexpr Vec4 Green		{ 0.0f, 1.0f, 0.0f, 1.0f };
		static constexpr Vec4 Blue		{ 0.0f, 0.0f, 1.0f, 1.0f };
		static constexpr Vec4 Yellow	{ 1.0f, 1.0f, 0.0f, 1.0f };
		static constexpr Vec4 Cyan		{ 0.0f, 1.0f, 1.0f, 1.0f };
		static constexpr Vec4 Megenta	{ 1.0f, 0.0f, 1.0f, 1.0f };

		inline Vec4 RgbToVec4(float r, float g, float b, float a = 1.0f)
		{
			return Vec4(r / 256.0f, g / 256.0f, b / 256.0f, a);
		}
	}

	
}

