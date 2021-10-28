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
		void UpdateEditor(float deltaTime);
		void UpdateInGame(float deltaTime);
		void UpdateWorldMatrix();
		void Shutdown();

		void AddComponent(const SPtr<Component>& component);
		void RemoveComponent(const WPtr<Component>& component);

	private:
		std::vector<SPtr<Component>> m_Components;

	public:
		void OnAllCompToFunction(std::function<void(const SPtr<Component>& comp)> function);
	};
}


