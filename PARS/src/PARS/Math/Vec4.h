#pragma once

namespace PARS
{
	class Vec4
	{
	public:
		float x;
		float y;
		float z;
		float w;

		Vec4() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
		Vec4(float inX, float inY, float inZ, float inW)
			: x(inX), y(inY), z(inZ), w(inW) {}

		friend Vec4 operator+(const Vec4& lhs, const Vec4& rhs);
		friend Vec4 operator-(const Vec4& lhs, const Vec4& rhs);
		friend Vec4 operator*(const Vec4& lhs, const Vec4& rhs);
		friend Vec4 operator*(const Vec4& lhs, float scalar);
		friend Vec4 operator*(float scalar, const Vec4& rhs);

		Vec4& operator+=(const Vec4& rhs);
		Vec4& operator-=(const Vec4& rhs);
		Vec4& operator*=(const Vec4& rhs);
		Vec4& operator*=(float scalar);

		friend bool operator==(const Vec4& lhs, const Vec4& rhs);
		friend bool operator!=(const Vec4& lhs, const Vec4& rhs);

		friend std::ostream& operator<<(std::ostream& os, const Vec4& vec);

		std::string ToString() const;

		static const Vec4 Zero;
	};

	namespace COLOR
	{
		static const Vec4 Black{ 0.0f, 0.0f, 0.0f, 1.0f };
		static const Vec4 White{ 1.0f, 1.0f, 1.0f, 1.0f };
		static const Vec4 Red{ 1.0f, 0.0f, 0.0f, 1.0f };
		static const Vec4 Green{ 0.0f, 1.0f, 0.0f, 1.0f };
		static const Vec4 Blue{ 0.0f, 0.0f, 1.0f, 1.0f };
		static const Vec4 Yellow{ 1.0f, 1.0f, 0.0f, 1.0f };
		static const Vec4 Cyan{ 0.0f, 1.0f, 1.0f, 1.0f };
		static const Vec4 Megenta{ 1.0f, 0.0f, 1.0f, 1.0f };

		inline Vec4 RgbToVec4(float r, float g, float b, float a = 1.0f)
		{
			return Vec4(r / 256.0f, g / 256.0f, b / 256.0f, a);
		}
	}
}