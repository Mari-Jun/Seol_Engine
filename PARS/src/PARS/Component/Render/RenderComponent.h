#pragma once
#include "PARS/Component/Component.h"

namespace PARS
{
	enum class RenderState
	{
		Ready,
		Changed,
		Render,
		Invisible
	};

	enum class RenderType
	{
		Mesh
	};

	class RenderComponent : public Component
	{
	public:
		RenderComponent(const std::string& name = "RenderComponent", RenderType type = RenderType::Mesh, int updateOrder = 200);
		virtual ~RenderComponent() = default;

		virtual void Initialize();
		virtual void Shutdown();
		virtual void Draw(ID3D12GraphicsCommandList* commandList) {}

		virtual void RenderReady(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) {}
		virtual void ReleaseUploadBuffers() {}

	public:
		void SetRenderState(RenderState state);
		RenderState GetRenderState() const { return m_RenderState; }

	protected:
		RenderState m_RenderState;
		RenderType m_Type;
	};
}