#pragma once

#include "PARS/Core/Core.h"
#include "PARS/Math/Math.h"

namespace PARS
{
	class Actor
	{
	public:
		enum class ActorState
		{
			Active, Paused, Dead
		};

		Actor();
		virtual ~Actor() = default;

		virtual void Initialize() {}
		virtual void Shutdown() {}
		virtual void ActorInput() {}
		void Update(float deltaTime);
		void UpdateComponents(float deltaTime);
		virtual void UpdateActor(float deltaTime) {}

		void UpdateWorldMatrix();

		void AddComponent();

	protected:
		ActorState m_ActorState;

	private:
		Mat4 m_WorldMatrix = Mat4::Identity;
		Vec3 m_Position = Vec3::Zero;
		Quaternion m_Rotation = Quaternion::Identity;
		float m_Scale = 1.0f;
		bool m_RechangeWorldMatrix = true;
		
		std::vector<SPtr<class Component>> m_Components;

	public:
		ActorState GetActorState() const { return m_ActorState; }
		void SetActorState(ActorState state) { m_ActorState = state; }
		void SetStateDead() { m_ActorState = ActorState::Dead; }

		const Mat4& GetWorldMatrix() const { return m_WorldMatrix; }
		const Vec3& GetPosition() const { return m_Position; }
		void SetPosition(const Vec3& pos) { m_Position = pos; m_RechangeWorldMatrix = true; }
		const Quaternion& GetRotation() const { return m_Rotation; }
		void SetRotation(const Quaternion& rot) { m_Rotation = rot; m_RechangeWorldMatrix = true; }
		float GetScale() const { return m_Scale; }
		void SetScale(float scale) { m_Scale = scale; m_RechangeWorldMatrix = true; }

		const Vec3& GetForward() const { return Vec3::Transform(Vec3::AxisZ, m_Rotation); }
		const Vec3& GetRight() const { return Vec3::Transform(Vec3::AxisX, m_Rotation); }
		const Vec3& GetUp() const { return Vec3::Transform(Vec3::AxisY, m_Rotation); }
	};
}


