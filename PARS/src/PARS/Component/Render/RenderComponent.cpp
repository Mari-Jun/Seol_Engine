#include "stdafx.h"
#include "PARS/Component/Render/RenderComponent.h"

namespace PARS
{
	RenderComponent::RenderComponent(const std::string& name, RenderType type, int updateOrder)
		: Component(name, updateOrder)
		, m_RenderType(type)
		, m_RenderState(RenderState::Ready)
	{
	}

	void RenderComponent::Initialize()
	{
		auto factory = RenderComponentFactory::GetRenderComponentFactory();
		factory->AddRenderComponent(m_RenderType, std::reinterpret_pointer_cast<RenderComponent>(shared_from_this()));
	}

	void RenderComponent::Shutdown()
	{
		auto factory = RenderComponentFactory::GetRenderComponentFactory();
		factory->RemoveRenderComponent(m_RenderType, std::reinterpret_pointer_cast<RenderComponent>(shared_from_this()));
	}

	void RenderComponent::SetRenderState(RenderState state)
	{
		m_RenderState = state;
		if (m_RenderState == RenderState::Ready)
		{
			auto factory = RenderComponentFactory::GetRenderComponentFactory();
			factory->AddPrepareComponent(m_RenderType, std::reinterpret_pointer_cast<RenderComponent>(shared_from_this()));
		}
	}
}
