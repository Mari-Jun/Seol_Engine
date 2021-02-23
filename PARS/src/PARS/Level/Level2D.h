#pragma once
#include "PARS/Level/Level.h"

#undef near
#undef far

namespace PARS
{
	class Level2D : public Level
	{
	public:
		Level2D(const std::string& name);
		virtual ~Level2D() = default;

		virtual void InitializeLevel();
		virtual	void ShutdownLevel() {}
		virtual void UpdateLevel(float deltaTime) {};

	protected:
		void SetRenderProjectionOrtho(float left, float right, float bottom, float top, float near = 0.0f, float far = 1.0f);

	public:
		void SetDefaultCameraActive();
		void SetDefaultCameraPause();

	private:
		SPtr<class CameraComponent> m_DefaultCamera;
		SPtr<class PlayerController> m_DefaultController;
	};

}

