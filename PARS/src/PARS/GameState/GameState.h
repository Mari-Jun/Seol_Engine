#pragma once
#include "PARS/Core/Core.h"

namespace PARS
{
	class Pawn;
	class PlayerController;

	class GameState
	{
	public:
		GameState() = default;
		virtual ~GameState() = default;

		virtual void Initialize() {}
		virtual void Shutdown();

		const SPtr<Pawn>& GetGamePawn() const { return m_DefaultPawn; }
		const SPtr<PlayerController>& GetGameController() const { return m_DefaultController; }
		void SetDefaultPawn(const SPtr<Pawn>& pawn) { m_DefaultPawn = pawn; }
		void SetDefaultController(const SPtr<PlayerController>& controller) { m_DefaultController = controller; }

	protected:
		SPtr<Pawn> m_DefaultPawn;
		SPtr<PlayerController> m_DefaultController;
	};

	class Default2DGameState : public GameState
	{
	public:
		Default2DGameState() = default;
		virtual ~Default2DGameState() = default;

		virtual void Initialize() override;
	};

	class Default3DGameState : public GameState
	{
	public:
		Default3DGameState() = default;
		virtual ~Default3DGameState() = default;

		virtual void Initialize() override;
	};
}


