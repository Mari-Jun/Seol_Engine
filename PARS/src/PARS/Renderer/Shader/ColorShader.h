#pragma once

#include "PARS/Renderer/Shader/Core/Shader.h"

namespace PARS
{
	class ColorShader : public Shader
	{
	public:
		ColorShader(SPtr<DirectX12>& directX);
		virtual ~ColorShader() = default;

	public:
		virtual void CreateShader() override;
		virtual void CreateInputLayout()  override;
		virtual bool CreatePSO(ID3D12RootSignature* rootSignature) override;
	};

}

