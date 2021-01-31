#include "stdafx.h"
#include "PARS/Component/ComponentManager.h"

namespace PARS
{
	ComponentManager::ComponentManager()
	{
	
	}

	void ComponentManager::Update(float deltaTime)
	{
		for (const auto& component : m_Components)
		{
			component->Update(deltaTime);
		}
	}

	void ComponentManager::Shutdown()
	{
		for (auto component : m_Components)
		{
			if (component != nullptr)
			{
				component->Shutdown();
			}
		}
	}

	void ComponentManager::AddComponent(const SPtr<Component>& component)
	{
		m_Components.emplace_back(component);
		component->Initialize();
	}

	void ComponentManager::RemoveComponent(const WPtr<Component>& component)
	{
		auto iter = std::find_if(m_Components.begin(), m_Components.end(),
			[&component](const WPtr<Component>& cp)
			{return component.lock() == cp.lock(); });
		if (iter != m_Components.end())
		{
			component.lock()->Shutdown();
			m_Components.erase(iter);
		}
	}
}