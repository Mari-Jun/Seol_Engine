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
		void SetUseDefaultKeyEvent(bool use);
		void SetUseDefaultMouseEvent(bool use);
		void SetSameRoationWithPawn(bool boolean) { b_IsSameRotationWithPawn = boolean; }

	private:
		void MoveForward(float axis);
		void MoveRightward(float axis);
	};
}


