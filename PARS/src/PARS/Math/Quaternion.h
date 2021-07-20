#pragma once

namespace PARS
{
	class Vec3;

	class Quaternion
	{
	public:
		float x, y, z, w;

		Quaternion();
		Quaternion(float x, float y, float z, float w);
		Quaternion(const Vec3& axis, float angle);

		Quaternion& operator*=(const Quaternion& q);
		friend Quaternion operator*(const Quaternion& p, const Quaternion& q);

		friend std::ostream& operator<<(std::ostream& os, const Quaternion& quat);

		Quaternion Conjugate() const;

		float LengthSq() const;
		float Length() const;

		void Normalize();
		static Quaternion Normalize(const Quaternion& q);

		static float Dot(const Quaternion& q1, const Quaternion& q2);
		static Quaternion Lerp(const Quaternion& q1, const Quaternion& q2, float f);
		static Quaternion Slerp(const Quaternion& p, const Quaternion& q, float f);

		std::string ToString() const;

		static const Quaternion Identity;
	};
}


