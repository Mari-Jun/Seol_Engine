#pragma once

#include "PARS/Core/Core.h"
#include "PARS/Renderer/DirectX12/DirectX12.h"
#include "PARS/Util/DirectX12/d3dUtil.h"
#include "PARS/Component/Render/RenderComponent.h"

namespace PARS
{
	enum class ShaderType
	{
		Color,
		Material
	};

	class Shader
	{
	public:
		Shader(const SPtr<DirectX12>& directX);
		virtual ~Shader() = default;

		virtual bool Initialize(ID3D12RootSignature* rootSignature);
		virtual void Shutdown();
		void Update(ID3D12Device* device, ID3D12GraphicsCommandList* commandList);
		virtual void Draw(ID3D12GraphicsCommandList* commandList);
		virtual void PrepareToNextDraw();

	private:
		virtual void Update() {}
		virtual void RenderReady(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, UINT newObjectCnt, UINT numOfObject) {}
		virtual void DrawRenderComp(ID3D12GraphicsCommandList* commandList, int index) {}
		virtual void DrawPassFrame(ID3D12GraphicsCommandList* commandList) {}

	public:
		virtual D3D12_RASTERIZER_DESC CreateRasterizerState();
		virtual D3D12_BLEND_DESC CreateBlendState();
		virtual D3D12_DEPTH_STENCIL_DESC CreateDepthStencilState();
		 
		ID3DBlob* CompileShader(std::wstring&& fileName, std::string&& entryPoint, std::string&& target);
		virtual void CreateShader() {}
		virtual void CreateInputLayout() {}
		virtual bool CreatePSO(ID3D12RootSignature* rootSignature) { return true; }

	public:
		void AddRenderComponent(const SPtr<class RenderComponent>& component);
		void AddPrepareComponent(const SPtr<class RenderComponent>& component);
		void RemoveRenderComponent(const SPtr<class RenderComponent>& component);
		
	public:
		ShaderType GetShaderType() const { return m_Type; }
		ID3D12PipelineState* GetPipelineState() const { return m_PipelineState; }

	protected:
		SPtr<DirectX12> m_DirectX12;

		ID3DBlob* m_VSBlob = nullptr;
		ID3DBlob* m_PSBlob = nullptr;

		std::vector<D3D12_INPUT_ELEMENT_DESC> m_InputLayouts;

		ID3D12PipelineState* m_PipelineState = nullptr;

		ShaderType m_Type;

	protected:
		std::vector<SPtr<class RenderComponent>> m_PrepareComponents;
		std::vector<SPtr<class RenderComponent>> m_RenderComponents;
		bool m_IsNeedUpdateMappedData = true;

	private:
		static std::wstring s_ShaderFilePath;
	};
}


