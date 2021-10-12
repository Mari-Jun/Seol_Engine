#include "stdafx.h"
#include "PARS/Component/Render/Texture/Texture.h"
#include "PARS/Renderer/Core/Viewport.h"
#include "PARS/Core/Window.h"

namespace PARS
{
	Viewport::Viewport()
	{
		m_ViewTexture = CreateSPtr<Texture>();
	}

	void Viewport::Shutdown()
	{
	}

	void Viewport::UpdateViewportSize(float left, float top, float width, float height)
	{
		RECT rect;
		GetWindowRect(Window::GetWindowInfo()->m_hwnd, &rect);
		POINT point = { static_cast<LONG>(left), static_cast<LONG>(top) };
		ScreenToClient(Window::GetWindowInfo()->m_hwnd, &point);

		if (point.x != m_Left)
		{
			m_Left = static_cast<float>(point.x);
			m_IsChangeViewport = true;
		}

		if (point.y != m_Top)
		{
			m_Top = static_cast<float>(point.y);
			m_IsChangeViewport = true;
		}

		if (width != m_Width)
		{
			m_Width = width;
			m_IsChangeViewport = true;
		}

		if (height != m_Height)
		{
			m_Height = height;
			m_IsChangeViewport = true;
		}
	}

	void Viewport::UpdateViewportTexture(ID3D12Device* device)
	{
		if (m_ViewTexture != nullptr)
		{
			m_ViewTexture->Shutdown();
		}

	/*	m_ViewTexture->CreateTexture(device, static_cast<UINT>(m_Width), static_cast<UINT>(m_Height),
			DXGI_FORMAT_R8G8B8A8_UNORM, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET, D3D12_RESOURCE_STATE_COMMON, nullptr, 0x01);*/
	}
}
