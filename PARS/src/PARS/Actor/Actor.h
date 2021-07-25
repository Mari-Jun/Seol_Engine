#pragma once

#include "PARS/Core/Core.h"
#include "PARS/Layer/DetailFunctionFactory.h"
#include "PARS/Actor/ActorDetailFunction.h"
#include "PARS/Component/ComponentManager.h"
#include "PARS/Input/InputFactory.h"
#include "PARS/Math/Math.h"

namespace PARS
{
	class Actor : public std::enable_shared_from_this<Actor>
	{
	public:
		enum class ActorState
		{
			Active, Paused, Dead
		};

		Actor(const std::string& name = "Actor");
		virtual ~Actor() = default;

		void InitializeActor();
		void ShutdownActor();
		virtual void Initialize() {}
		virtual void InitializeDetailFunction();
		virtual void Shutdown() {}
		void ProcessInput();
		virtual void ActorInput() {}
		void UpdateActor(float deltaTime);
		virtual void Update(float deltaTime) {}

		void UpdateWorldMatrix();

		void AddComponent(const SPtr<class Component>& component);
		void RemoveComponent(const SPtr<class Component>& component);
		void AddDetailFunctionInfo(FunctionInfo&& info);

	public:
		void AddOnceAction(std::string&& name, int key, const std::function<void()>& func);
		void AddLoopAction(std::string&& name, int key, const std::function<void()>& func);
		void AddAxisAction(std::string&& name, std::vector<KeyAxis>&& keyAndAxis, const std::function<void(float)>& func);
		void AddReleaseAction(std::string&& name, int key, const std::function<void()>& func);
		void ActiveAction(ActionType type, std::string&& name, bool active);

	protected:
		std::string m_ActorName;
		ActorState m_ActorState;
		UPtr<ActorDetailFunction> m_DetailFunction;

	private:
		
		Mat4 m_WorldMatrix = Mat4::Identity;
		Vec3 m_Position = Vec3::Zero;
		Quaternion m_Rotation = Quaternion::Identity;
		Vec3 m_Scale = Vec3::One;
		bool m_RechangeWorldMatrix = true;

		UPtr<ComponentManager> m_ComponentManager;
		UPtr<DetailFunctionFactory> m_DetailFunctionFactory;
		UPtr<InputFactory> m_InputFactory;

	public:
		const std::string& GetActorName() const { return m_ActorName; }
		void SetActorName(const std::string& name) { m_ActorName = name; }
		ActorState GetActorState() const { return m_ActorState; }
		void SetActorState(ActorState state) { m_ActorState = state; }
		void SetStateDead() { m_ActorState = ActorState::Dead; }

		const Mat4& GetWorldMatrix() const { return m_WorldMatrix; }
		const Vec3& GetPosition() const { return m_Position; }
		void SetPosition(const Vec3& pos) { m_Position = pos; m_RechangeWorldMatrix = true; }
		const Quaternion& GetRotation() const { return m_Rotation; }
		void SetRotation(const Quaternion& rot) { m_Rotation = rot; m_RechangeWorldMatrix = true; }
		const Vec3& GetScale() const { return m_Scale; }
		void SetScale(const Vec3& scale) { m_Scale = scale; m_RechangeWorldMatrix = true;}
		void SetScale(float scale) { m_Scale = Vec3::One * scale; m_RechangeWorldMatrix = true; }

		Vec3 GetForward() const { return Vec3::Transform(Vec3::AxisZ, m_Rotation); }
		Vec3 GetRight() const { return Vec3::Transform(Vec3::AxisX, m_Rotation); }
		Vec3 GetUp() const { return Vec3::Transform(Vec3::AxisY, m_Rotation); }

		const std::vector<FunctionInfo>& GetDetailFunctionInfos() const { return m_DetailFunctionFactory->GetFunctionInfos(); }
	};
}


