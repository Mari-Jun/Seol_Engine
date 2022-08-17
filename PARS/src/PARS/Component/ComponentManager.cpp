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

	void ComponentManager::UpdateEditor(float deltaTime)
	{
		for (const auto& component : m_Components)
		{
			component->UpdateOnlyEditor(deltaTime);
		}
	}

	void ComponentManager::UpdateInGame(float deltaTime)
	{
		for (const auto& component : m_Components)
		{
			component->UpdateOnlyInGame(deltaTime);
		}
	}

	void ComponentManager::UpdateWorldMatrix()
	{
		for (const auto& component : m_Components)
		{
			component->UpdateWorldMatrix();
		}
	}

	void ComponentManager::Shutdown()
	{
		for (auto component : m_Components)
		{
			if (component != nullptr)
			{
				component->ShutdownComponent();
			}
		}
	}

	void ComponentManager::AddComponent(const SPtr<Component>& component)
	{
		m_Components.emplace_back(component);
		component->InitializeComponent();
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

	void ComponentManager::OnAllCompToFunction(std::function<void(const SPtr<Component>& comp)> function)
	{
		for (const auto& comp : m_Components)
		{
			function(comp);
		}
	}
}