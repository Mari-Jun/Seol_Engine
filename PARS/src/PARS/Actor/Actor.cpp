#include "stdafx.h"
#include "PARS/Actor/Actor.h"

#include "imgui.h"

namespace PARS
{
	Actor::Actor(const std::string& name)
		: m_ActorName(name)
		, m_ActorState(ActorState::Active)
	{
		m_DetailFuncManager = CreateUPtr<DetailFunctionManager>();
		m_ComponentManager = CreateUPtr<ComponentManager>();
		m_InputFactory = CreateUPtr<InputFactory>();
	}

	void Actor::InitializeActor()
	{
		AddDetailFunction([this]() {ActorDetail(); });
		Initialize();
	}

	void Actor::ShutdownActor()
	{
		Shutdown();
		m_ComponentManager->Shutdown();
	}

	void Actor::ProcessInput()
	{
		ActorInput();
		m_InputFactory->ProcessInput();
	}

	void Actor::UpdateActor(float deltaTime)
	{
		UpdateWorldMatrix();

		m_ComponentManager->Update(deltaTime);
		Update(deltaTime);
		
		UpdateWorldMatrix();
	}

	void Actor::UpdateWorldMatrix()
	{
		if (m_RechangeWorldMatrix)
		{
			//Change Actor World Matrix
			m_WorldMatrix = Mat4::CreateScale(m_Scale);
			m_WorldMatrix *= Mat4::CreateRotationFromQuaternion(m_Rotation);
			m_WorldMatrix *= Mat4::CreateTranslation(m_Position);

			//Change Component World Matrix
			m_ComponentManager->UpdateWorldMatrix();

			m_RechangeWorldMatrix = false;
		}
	}

	void Actor::AddDetailFunction(const std::function<void()>& func, const std::string& triName)
	{
		m_DetailFuncManager->AddDetailFunction(triName, func);
	}

	void Actor::AddComponent(const SPtr<class Component>& component)
	{
		m_ComponentManager->AddComponent(component);
		component->SetOwner(weak_from_this());
	}

	void Actor::RemoveComponent(const SPtr<class Component>& component)
	{
		m_ComponentManager->RemoveComponent(component);
	}

	void Actor::AddOnceAction(std::string&& name, int key, const std::function<void()>& func)
	{
		m_InputFactory->AddOnceAction(std::move(name), key, func);
	}

	void Actor::AddLoopAction(std::string&& name, int key, const std::function<void()>& func)
	{
		m_InputFactory->AddLoopAction(std::move(name), key, func);
	}

	void Actor::AddAxisAction(std::string&& name, std::vector<KeyAxis>&& keyAndAxis, const std::function<void(float)>& func)
	{
		m_InputFactory->AddAxisAction(std::move(name), std::move(keyAndAxis), func);
	}

	void Actor::AddReleaseAction(std::string&& name, int key, const std::function<void()>& func)
	{
		m_InputFactory->AddReleaseAction(std::move(name), key, func);
	}

	void Actor::ActiveAction(ActionType type, std::string&& name, bool active)
	{
		m_InputFactory->ActiceAction(type, std::move(name), active);
	}

	void Actor::ActorDetail()
	{
		static ImVec4 textColor = ImVec4(0.0f, 1.0f, 1.0f, 1.0f);

		ImGui::TextColored(textColor, "Position");
		std::ostringstream stream;
		stream << GetPosition();
		ImGui::BulletText(stream.str().c_str());

		stream.str("");
		stream.clear();

		ImGui::TextColored(textColor, "Rotation");
		stream << GetRotation();
		ImGui::BulletText(stream.str().c_str());
	}
}
