#pragma once
#include "stdafx.h"

namespace PARS::Math
{
	static constexpr float Pi = XM_PI;
	static constexpr float TwoPi = XM_2PI;
	static constexpr float PiDiv2 = XM_PIDIV2;

	inline float ToRadians(float degrees)
	{
		return degrees * Pi / 180.0f;
	}

	inline float ToDegrees(float radian)
	{
		return radian * 180.0f / Pi;
	}

	inline bool NearZero(float value, float spsilon = 0.001f)
	{
		return (fabs(value) <= spsilon);
	}

	inline float Abs(float value)
	{
		return fabs(value);
	}

	inline float Sin(float angle)
	{
		return sinf(angle);
	}

	inline float Cos(float angle)
	{
		return cosf(angle);
	}

	inline float Tan(float angle)
	{
		return tanf(angle);
	}

	inline float Asin(float angle)
	{
		return asinf(angle);
	}

	inline float Acos(float angle)
	{
		return acosf(angle);
	}

	inline float Atan(float angle)
	{
		return atanf(angle);
	}

	inline float Atan2(float y, float x)
	{
		return atan2f(y, x);
	}

	inline float Cot(float angle)
	{
		return 1.0f / Tan(angle);
	}

	inline float Sqrt(float value)
	{
		return sqrtf(value);
	}

	template <typename T>
	T Max(const T& a, const T& b)
	{
		return (a < b) ? b : a;
	}

	template <typename T>
	T Min(const T& a, const T& b)
	{
		return (a < b) ? a : b;
	}

	template <typename T>
	T Clamp(const T& value, const T& min, const T& max)
	{
		return Min(max, Max(min, value));
	}
}