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
		virtual void Update(float deltaTime) override;

	private:
		bool b_IsSameRotationWithPawn = true;

	public:
		void SetSameRoationWithPawn(bool boolean) { b_IsSameRotationWithPawn = boolean; }

	public:
		void MoveForward(float axis);
		void MoveRightward(float axis);
		void MoveUpward(float axis);
		void TurnAxisY(float axis);
		void TurnAxisX(float axis);
	};
}


