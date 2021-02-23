#pragma once
#include "PARS/Actor/Actor.h"
#include "PARS/Component/Util/MovementComponent.h"

namespace PARS
{
	class Pawn : public Actor
	{
	public:
		Pawn();
		virtual ~Pawn() = default;

		virtual void Initialize() override;
		virtual void Shutdown() override;
		virtual void Update(float deltaTime) {}

	protected:
		SPtr<MovementComponent> m_MovementComp;

	public:
		const SPtr<MovementComponent>& GetMovementComp() const { return m_MovementComp; }
	};
}


