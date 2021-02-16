#pragma once

#include "PARS/Component/Component.h"
#include "PARS/Renderer/Core/RenderFactory.h"

namespace PARS
{
	class RenderComponent : public Component
	{
	public:
		RenderComponent(const WPtr<Actor>& owner, int updateOrder = 200);
		virtual ~RenderComponent() = default;

		virtual void Initialize();
		virtual void Shutdown();
		virtual void Draw(ID3D12GraphicsCommandList* commandList) {}
		virtual void RenderReady(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) {}

	protected:
		ShaderType m_RenderShaderType;
	};
}