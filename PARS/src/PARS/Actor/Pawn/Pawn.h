#pragma once
#include "PARS/Actor/Actor.h"
#include "PARS/Component/Util/Movement/MovementComponent.h"

namespace PARS
{
	class Pawn : public Actor
	{
	public:
		Pawn(const std::string& name = "Pawn");
		virtual ~Pawn() = default;

		virtual void Initialize() override;
		virtual void Shutdown() override;

		//virtual void PossessPlayer(int playerIndex = 0);

	protected:
		SPtr<MovementComponent> m_MovementComp;

	public:
		const SPtr<MovementComponent>& GetMovementComp() const { return m_MovementComp; }
	};
}


