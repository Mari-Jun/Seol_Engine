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
		virtual void LevelInput() {}
		virtual void UpdateLevel(float deltaTime) {};

	protected:
		void SetRenderProjectionOrtho(float left, float right, float bottom, float top, float near = 0.0f, float far = 1.0f);

	public:
		void SetDefaultCameraActive();
		void SetDefaultCameraPause();

		//외부에서 카메라 컨트롤러를 세팅할 수 있게 (원한다면)

	private:
		SPtr<class CameraComponent> m_Camera;

		//기본 컨트롤러 선언
	};

}

