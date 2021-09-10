#pragma once
#include "PARS/Renderer/Shader/Core/Shader.h"

namespace PARS
{
	class MaterialShader : public Shader
	{
	public:
		MaterialShader(const SPtr<DirectX12>& directX);

		virtual ~MaterialShader() = default;

	public:
		virtual void CreateShader() override;
		virtual void CreateInputLayout()  override;
		virtual bool CreatePSO(ID3D12RootSignature * rootSignature) override;
	};
}


