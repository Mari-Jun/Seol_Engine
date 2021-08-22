#pragma once
#include "PARS/Component/Camera/CameraComponent.h"	

namespace PARS
{
	class Viewport
	{
	public:
		Viewport() = default;
		virtual ~Viewport() = default;

	public:
		void SetLeft(float left);
		void SetTop(float top);
		void SetWidth(float width);
		void SetHeight(float height);

		float GetLeft() const { return m_Left; }
		float GetTop() const { return m_Top; }
		float GetWidth() const { return m_Width; }
		float GetHeight() const { return m_Height; }

		bool IsChangeViewport() const { return m_IsChangeViewport; }
		void ChangedViewport() { m_IsChangeViewport = false; }

	private:
		float m_Left = 0.0f, m_Top = 0.0f, m_Width = 0.0f, m_Height = 0.0f;
		bool m_IsChangeViewport = false;

	public:
		const WPtr<CameraComponent>& GetCameraOwner() const { return m_CameraOwner; }
		void SetCamera(const WPtr<CameraComponent>& camera) { m_CameraOwner = camera; m_IsChangeViewport = true; }

	private:
		WPtr<CameraComponent> m_CameraOwner;
	};
}


