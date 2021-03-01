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

		virtual void InitializeLevel() override;

	protected:
		void SetDefaultCameraActive();
		void SetDefaultCameraPause();
		virtual void SetDefaultControllerKeyEvent(bool use) {}
		virtual void SetDefaultControllerMouseEvent(bool use) {}

	protected:
		SPtr<class Pawn> m_DefaultPawn = nullptr;
		SPtr<class CameraComponent> m_DefaultCamera = nullptr;
		SPtr<class PlayerController> m_DefaultController = nullptr;

	protected:
		const SPtr<class Pawn>& GetDefaultPawn() const { return m_DefaultPawn; }
		const SPtr<class PlayerController>& GetDefaultController() const { return m_DefaultController; }
	};

	class Level2D : public DefaultLevel
	{
	public:
		Level2D(const std::string& name);
		virtual ~Level2D() = default;

		virtual void InitializeLevel() override;

	protected:
		virtual void SetDefaultControllerKeyEvent(bool use) override final;
		virtual void SetDefaultControllerMouseEvent(bool use) override final;
		void SetRenderProjectionOrtho(float left, float right, float bottom, float top, float near = 0.0f, float far = 1.0f);

	};

	class Level3D : public DefaultLevel
	{
	public:
		Level3D(const std::string& name);
		virtual ~Level3D() = default;

		virtual void InitializeLevel() override;

	protected:
		virtual void SetDefaultControllerKeyEvent(bool use) override final;
		virtual void SetDefaultControllerMouseEvent(bool use) override final;
		void SetRenderProjectionPerspective(float fovy, float aspect, float near = 1.0f, float far = 10000.0f);

	};

}

