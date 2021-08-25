#include "stdafx.h"
#include "PARS/Component/Render/RenderComponent.h"
#include "PARS/Renderer/Core/RenderFactory.h"


namespace PARS
{
	RenderComponent::RenderComponent(const std::string& name, RenderType type, int updateOrder)
		: Component(name, updateOrder)
		, m_RenderState(RenderState::Ready)
		, m_Type(type)
	{
	}

	void RenderComponent::Initialize()
	{
		auto factory = RenderFactory::GetRenderFactory();
		factory->AddRenderComponent(m_Type, std::reinterpret_pointer_cast<RenderComponent>(shared_from_this()));
	}

	void RenderComponent::Shutdown()
	{
		auto factory = RenderFactory::GetRenderFactory();
		factory->RemoveRenderComponent(m_Type, std::reinterpret_pointer_cast<RenderComponent>(shared_from_this()));
	}

	void RenderComponent::SetRenderState(RenderState state)
	{
		m_RenderState = state;
		if (m_RenderState == RenderState::Changed)
		{
			auto factory = RenderFactory::GetRenderFactory();
			factory->AddPrepareComponent(m_Type, std::reinterpret_pointer_cast<RenderComponent>(shared_from_this()));
		}
	}
}
