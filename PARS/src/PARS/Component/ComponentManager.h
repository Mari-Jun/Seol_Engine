#pragma once

#include "PARS/Component/Component.h"

namespace PARS
{
	class ComponentManager final
	{
	public:
		ComponentManager();
		~ComponentManager() = default;

		void Update(float deltaTime);
		void Shutdown();

		void AddComponent(const SPtr<Component>& component);
		void RemoveComponent(const WPtr<Component>& component);

	private:
		std::vector<SPtr<Component>> m_Components;
	};
}


