#pragma once

#include "PARS/Component/Component.h"
#include "PARS/Renderer/Core/RenderFactory.h"

namespace PARS
{
	class RenderComponent : public Component
	{
	public:
		RenderComponent(RenderType type = RenderType::Mesh, int updateOrder = 200);
		virtual ~RenderComponent() = default;

		virtual void Initialize();
		virtual void Shutdown();
		virtual void Draw(ID3D12GraphicsCommandList* commandList) {}

		virtual void RenderReady(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) {}
		virtual void ReleaseUploadBuffers() {}

	protected:
		void ChangeComponentItem();

	protected:
		RenderType m_RenderType;
	};
}