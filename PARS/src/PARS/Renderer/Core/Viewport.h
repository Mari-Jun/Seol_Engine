#pragma once

namespace PARS
{
	class Texture;

	class Viewport
	{
	public:
		Viewport();
		virtual ~Viewport() = default;

		void Shutdown();

	public:
		void UpdateViewportSize(float left, float top, float width, float height);
		void UpdateViewportTexture(ID3D12Device* device);

		float GetLeft() const { return m_Left; }
		float GetTop() const { return m_Top; }
		float GetWidth() const { return m_Width; }
		float GetHeight() const { return m_Height; }

		bool IsChangeViewport() const { return m_IsChangeViewport; }
		void ChangedViewport() { m_IsChangeViewport = false; }

	private:
		float m_Left = 0.0f, m_Top = 0.0f, m_Width = 0.0f, m_Height = 0.0f;
		bool m_IsChangeViewport = false;

	private:
		SPtr<Texture> m_ViewTexture;
		ID3D12DescriptorHeap* m_TextureDescriptorHeap = nullptr;
	};
}


