#include "stdafx.h"
#include "PARS/Level/DefaultLevel.h"
#include "PARS/Core/Window.h"
#include "PARS/Actor/Pawn/DefaultPawn.h"
#include "PARS/Actor/Controller/PlayerController.h"
#include "PARS/Input/Input.h"

namespace PARS
{
	DefaultLevel::DefaultLevel(const std::string& name)
		: Level(name)
	{
	}

	void DefaultLevel::InitializeLevel()
	{
		if (m_GameState != nullptr)
		{
			m_GameState->Initialize();

			AddActor(m_GameState->GetGamePawn());
			AddActor(m_GameState->GetGameController());
		}
		else
		{
			PARS_ERROR("Please check game state");
		}

		AddOnceAction("Mouse RButton", PARS_MOUSE_RBUTTON, [this]() {Input::SetCursorHide(true); }, true);
		AddReleaseAction("Mouse RButton", PARS_MOUSE_RBUTTON, [this]() {Input::SetCursorHide(false); }, true);

		AddOnceAction("InGame Cursor", PARS_KEY_BACKTICK, [this]() {InGameCursor(); });
	}

	void DefaultLevel::InGameCursor()
	{
		Input::SetCursorHide(!Input::IsCursorHide());
	}

	Level2D::Level2D(const std::string& name)
		: DefaultLevel(name)
	{
		m_GameState = CreateUPtr<Default2DGameState>();
	}

	void Level2D::InitializeLevel()
	{
		DefaultLevel::InitializeLevel();

		const auto& playerController = m_GameState->GetGameController();

		AddAxisAction("Move Rightward",
			std::vector{ KeyAxis{PARS_KEY_D, 1.0f, PARS_MOUSE_RBUTTON }, KeyAxis{PARS_KEY_A, -1.0f, PARS_MOUSE_RBUTTON} },
			[this, playerController](float axis) {playerController->MoveRightward(axis); }, true);
		AddAxisAction("Move Upward",
			std::vector{ KeyAxis{PARS_KEY_W, 1.0f, PARS_MOUSE_RBUTTON }, KeyAxis{PARS_KEY_S, -1.0f, PARS_MOUSE_RBUTTON} },
			[this, playerController](float axis) {playerController->MoveUpward(axis); }, true);

	}

	Level3D::Level3D(const std::string& name)
		: DefaultLevel(name)
	{
		m_GameState = CreateUPtr<Default3DGameState>();
	}

	void Level3D::InitializeLevel()
	{
		DefaultLevel::InitializeLevel();

		const auto& playerController = m_GameState->GetGameController();

		AddAxisAction("Move Forward",
			std::vector{ KeyAxis{PARS_KEY_W, 1.0f, PARS_MOUSE_RBUTTON }, KeyAxis{PARS_KEY_S, -1.0f, PARS_MOUSE_RBUTTON} },
			[this, playerController](float axis) {playerController->MoveForward(axis); }, true);
		AddAxisAction("Move Rightward",
			std::vector{ KeyAxis{PARS_KEY_D, 1.0f , PARS_MOUSE_RBUTTON}, KeyAxis{PARS_KEY_A, -1.0f, PARS_MOUSE_RBUTTON} },
			[this, playerController](float axis) {playerController->MoveRightward(axis); }, true);
		AddAxisAction("Move Upward",
			std::vector{ KeyAxis{PARS_KEY_E, 1.0f, PARS_MOUSE_RBUTTON }, KeyAxis{PARS_KEY_Q, -1.0f, PARS_MOUSE_RBUTTON} },
			[this, playerController](float axis) {playerController->MoveUpward(axis); }, true);
		AddAxisAction("Turn", std::vector{ KeyAxis{PARS_MOUSE_XMOVE, 1.0f, PARS_MOUSE_RBUTTON} },
			[this, playerController](float axis) {playerController->Turn(axis); }, true);
		AddAxisAction("LookUp", std::vector{ KeyAxis{PARS_MOUSE_YMOVE, 1.0f, PARS_MOUSE_RBUTTON} },
			[this, playerController](float axis) {playerController->LookUp(axis); }, true);
	}
}