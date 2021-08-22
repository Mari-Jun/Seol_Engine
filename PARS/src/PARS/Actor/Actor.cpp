#include "stdafx.h"
#include "PARS/Actor/Actor.h"

namespace PARS
{
	Actor::Actor(const std::string& name)
		: m_ActorName(name)
		, m_ActorState(ActorState::Active)
	{
		m_ComponentManager = CreateUPtr<ComponentManager>();
		m_InputFactory = CreateUPtr<InputFactory>();
	}

	void Actor::InitializeActor()
	{
		InitializeDetailFunction();
		if (m_DetailFunction != nullptr)
		{
			m_DetailFunction->Initialize(weak_from_this());
		}
		Initialize();
	}

	void Actor::ShutdownActor()
	{
		Shutdown();
		m_ComponentManager->Shutdown();
	}

	void Actor::InitializeDetailFunction()
	{
		m_DetailFunction = CreateUPtr<ActorDetailFunction>();
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
			m_IsChangedWorldMatrix = true;
		}
	}

	void Actor::AddComponent(const SPtr<class Component>& component)
	{
		component->SetOwner(weak_from_this());
		m_ComponentManager->AddComponent(component);
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

	std::string Actor::GetNameOfClass() const
	{
		std::stringstream ss;
		ss << typeid(*this).name();
		return ss.str().substr(12);
	}

	void Actor::AddDetailFunctionInfo(FunctionInfo&& info)
	{
		m_DetailFunction->AddFunctionInfo(std::move(info));
	}

	void Actor::OnUpdateDetailInfo(std::function<void(const DetailInfo& info)> function)
	{
		function(m_DetailFunction->GetDetailInfo());
		m_ComponentManager->OnAllCompToFunction([this, function](const SPtr<Component>& comp)
			{
				comp->OnUpdateDetailInfo(function);
			});
	}

	void Actor::SetDetailVisibleState(DVS state)
	{
		m_DetailFunction->SetDetailVisibleState(state);
		if (state == DVS::HideAll)
		{
			m_ComponentManager->OnAllCompToFunction([this, state] (const SPtr<Component>& comp)
				{
					comp->SetDetailVisibleState(state);
				});
		}
	}
	
	void Actor::SetFunctionVisibleState(const std::string& treeName, FVS state)
	{
		m_DetailFunction->SetFunctionVisibleState(treeName, state);
	}
}
