#pragma once

#include "PARS/Math/Math.h"

namespace PARS
{
	class Vertex
	{
	public:
		Vertex() : m_Position(Vec3::Zero), m_Normal({ 0.0f, 0.0f, -1.0f }) {}
		Vertex(Vec3&& position) : m_Position(position), m_Normal({ 0.0f, 0.0f, -1.0f }) {}
		Vertex(Vec3&& position, Vec3&& normal) : m_Position(position), m_Normal(normal) {}

		const Vec3& GetPosition() const { return m_Position; }
		void SetPosition(const Vec3& position) { m_Position = position; }

		const Vec3& GetNormal() const { return m_Normal; }
		void SetNormal(const Vec3& normal) { m_Normal = normal; }

	protected:
		Vec3 m_Position;
		Vec3 m_Normal;
	};

	class DiffuseVertex : public Vertex
	{
	public:
		DiffuseVertex() : Vertex(), m_DiffuseColor(COLOR::Black) {}
		DiffuseVertex(Vec3&& position, Vec4&& color) : Vertex(std::move(position)), m_DiffuseColor(color) {}
		DiffuseVertex(Vec3&& position, Vec3&& normal, Vec4&& color) : Vertex(std::move(position), std::move(normal)), m_DiffuseColor(color) {}

		const Vec4& GetDiffuseColor() const { return m_DiffuseColor; }
		void SetDiffuseColor(const Vec4& color) { m_DiffuseColor = color; }

	protected:
		Vec4 m_DiffuseColor;
	};

	class MaterialVertex : public Vertex
	{
	public:
		MaterialVertex() : Vertex(), m_MatIndex(0) {}
		MaterialVertex(Vec3 && position, int matIndex) : Vertex(std::move(position)), m_MatIndex(matIndex) {}
		MaterialVertex(Vec3 && position, Vec3 && normal, int matIndex) : Vertex(std::move(position), std::move(normal)), m_MatIndex(matIndex) {}

		int GetMaterialIndex() const { return m_MatIndex; }
		void SetMaterialIndex(int matIndex) { m_MatIndex = matIndex; }

	protected:
		int m_MatIndex;
	};
}