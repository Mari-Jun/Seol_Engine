#pragma once

#undef near
#undef far

namespace PARS
{
	class Vec3;
	class Quaternion;

	class Mat4
	{
	public:
		float mat[4][4];

		Mat4();
		Mat4(float* mat);
		Mat4(float m11, float m12, float m13, float m14,
			float m21, float m22, float m23, float m24,
			float m31, float m32, float m33, float m34,
			float m41, float m42, float m43, float m44);

		friend Mat4 operator*(const Mat4& lhs, const Mat4& rhs);
		Mat4& operator*=(const Mat4& mat);

		friend std::ostream& operator<<(std::ostream& os, const Mat4& mat);

		void Invert();

		Vec3 GetTranslation() const;

		static Mat4 CreateScale(float x, float y, float z);
		static Mat4 CreateScale(float scale);
		static Mat4 CreateScale(const Vec3& vec);
		static Mat4 CreateRotationX(float angle);
		static Mat4 CreateRotationY(float angle);
		static Mat4 CreateRotationZ(float angle);
		static Mat4 CreateRotationFromQuaternion(const Quaternion& q);
		static Mat4 CreateTranslation(float x, float y, float z);
		static Mat4 CreateTranslation(const Vec3& vec);

		static Mat4 LookAt(const Vec3& eye, const Vec3& target, const Vec3& up);
		static Mat4 Ortho(float left, float right, float bottom, float top, float near, float far);
		static Mat4 Perspective(float fovy, float aspect, float near, float far);

		void Transpose();
		static Mat4 Transpose(const Mat4& mat);

		XMMATRIX ConvertToXMMATRIX();
		void ConvertFromXMMATRIX(const XMMATRIX& matrix);

		std::string ToString() const;

		static const Mat4 Identity;
	};
}



