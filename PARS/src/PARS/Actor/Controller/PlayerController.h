#pragma once
#include "PARS/Actor/Controller/Controller.h"

namespace PARS
{
	class PlayerController : public Controller
	{
	public:
		PlayerController(const std::string& name = "PlayerController");
		PlayerController(const SPtr<class Pawn>& pawn, const std::string& name = "PlayerController");
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

	public:
		void MoveForward(float axis);
		void MoveRightward(float axis);
		void MoveUpward(float axis);
		void Turn(float axis);
		void LookUp(float axis);
	};

	class PlayerController2D : public PlayerController
	{
	public:
		PlayerController2D(const std::string& name = "Player Controller 2D");
		PlayerController2D(const SPtr<class Pawn>& pawn, const std::string& name = "Player Controller 2D");
		virtual ~PlayerController2D() = default;

		virtual void Initialize() override;
	};

	class PlayerController3D : public PlayerController
	{
	public:
		PlayerController3D(const std::string& name = "Player Controller 3D");
		PlayerController3D(const SPtr<class Pawn>& pawn, const std::string& name = "Player Controller 3D");
		virtual ~PlayerController3D() = default;

		virtual void Initialize() override;
	};
}


