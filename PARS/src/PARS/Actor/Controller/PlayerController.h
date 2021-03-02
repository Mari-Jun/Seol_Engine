#pragma once
#include "PARS/Actor/Controller/Controller.h"

namespace PARS
{
	class PlayerController : public Controller
	{
	public:
		PlayerController();
		PlayerController(const SPtr<class Pawn>& pawn);
		virtual ~PlayerController() = default;

		virtual void Initialize() override;
		virtual void Shutdown() override {}
		virtual void ActorInput() override;
		virtual void Update(float deltaTime) override;

	protected:
		SPtr<MovementComponent> m_MovementComp;

	private:
		bool b_IsSameRotationWithPawn = true;

	public:
		const SPtr<MovementComponent>& GetMovementComp() const { return m_MovementComp; }
		void SetSameRoationWithPawn(bool boolean) { b_IsSameRotationWithPawn = boolean; }

	private:
		float m_Pitch = 0.0f;

	public:
		void MoveForward(float axis);
		void MoveRightward(float axis);
		void MoveUpward(float axis);
		void TurnMouse();
	};
}


