#include "stdafx.h"
#include "PARS/Component/Render/RenderComponent.h"

namespace PARS
{
	RenderComponent::RenderComponent(RenderType type, int updateOrder)
		: Component(updateOrder)
		, m_RenderType(type)
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

	void RenderComponent::ChangeComponentItem()
	{
		auto factory = RenderComponentFactory::GetRenderComponentFactory();
		factory->MoveToPrepareComponent(m_RenderType, std::reinterpret_pointer_cast<RenderComponent>(shared_from_this()));
	}
}
