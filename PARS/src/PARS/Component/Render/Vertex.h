#pragma once

#include "PARS/Math/Math.h"

namespace PARS
{
	class Vertex
	{
	public:
		Vertex() : m_Position(Vec3::Zero) {}
		Vertex(Vec3&& position) : m_Position(position) {}
		~Vertex() {}

	protected:
		Vec3 m_Position;
	};

	class DiffuseVertex : public Vertex
	{
	public:
		DiffuseVertex() : Vertex(), m_DiffuseColor(COLOR::Black) {}
		DiffuseVertex(Vec3&& position, Vec4&& color) : Vertex(std::move(position)), m_DiffuseColor(color) {}
		~DiffuseVertex() {}

	protected:
		Vec4 m_DiffuseColor;
	};
}