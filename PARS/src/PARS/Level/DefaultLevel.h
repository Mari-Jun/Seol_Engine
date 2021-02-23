#pragma once
#include "PARS/Level/Level.h"

#undef near
#undef far

namespace PARS
{
	class DefaultLevel : public Level
	{
	public:
		DefaultLevel(const std::string& name);
		virtual ~DefaultLevel() = default;

		virtual void InitializeLevel();
		virtual	void ShutdownLevel() {}
		virtual void UpdateLevel(float deltaTime) {};

	protected:
		void SetDefaultCameraActive();
		void SetDefaultCameraPause();
		void SetDefaultControllerKeyEvent(bool use);
		void SetDefaultControllerMouseEvent(bool use);

	private:
		SPtr<class Pawn> m_DefaultPawn = nullptr;
		SPtr<class CameraComponent> m_DefaultCamera = nullptr;
		SPtr<class PlayerController> m_DefaultController = nullptr;

	protected:
		const SPtr<class PlayerController>& GetDefaultController() const { return m_DefaultController; }
	};

	class Level2D : public DefaultLevel
	{
	public:
		Level2D(const std::string& name);
		virtual ~Level2D() = default;

		virtual void InitializeLevel();
		virtual	void ShutdownLevel() {}
		virtual void UpdateLevel(float deltaTime) {};

	protected:
		void SetRenderProjectionOrtho(float left, float right, float bottom, float top, float near = 0.0f, float far = 1.0f);
	};

}

