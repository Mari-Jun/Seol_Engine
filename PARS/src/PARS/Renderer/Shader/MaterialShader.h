#pragma once
#include "PARS/Renderer/Shader/Core/Shader.h"

namespace PARS
{
	class MaterialShader : public Shader
	{
	public:
		MaterialShader(const SPtr<DirectX12>& directX);

		virtual ~MaterialShader() = default;
		virtual void Shutdown() override;
		virtual void PrepareToNextDraw() override;

	private:
		virtual void Update() override;
		virtual void RenderReady(ID3D12Device * device, ID3D12GraphicsCommandList * commandList, UINT newObjectCnt, UINT numOfObject) override;
		void UpdateShaderVariables();
		virtual void DrawRenderComp(ID3D12GraphicsCommandList * commandList, int index) override;

	public:
		virtual void CreateShader() override;
		virtual void CreateInputLayout()  override;
		virtual bool CreatePSO(ID3D12RootSignature * rootSignature) override;

	protected:
		ID3D12Resource* m_WorldMatCB = nullptr;
		BYTE* m_WorldMatMappedData = nullptr;

		ID3D12Resource* m_ConvertMatIndexCB = nullptr;
		BYTE* m_ConvertMatIndexMappedData = nullptr;
	};
}


