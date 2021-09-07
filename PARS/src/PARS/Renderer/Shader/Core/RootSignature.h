#pragma once
#include "PARS/Renderer/Shader/Core/Shader.h"	

namespace PARS
{
	struct CBPass
	{};

	class RootSignature
	{
	public:
		RootSignature(const SPtr<DirectX12>& directX);
		virtual ~RootSignature() = default;

		void Initialize(ID3D12Device* device);
		virtual void Shutdown();
		void Update(ID3D12Device* device, ID3D12GraphicsCommandList* commandList);
		void Draw(ID3D12GraphicsCommandList* commandList);
		void PrepareToNextDraw();

	private:
		virtual void CreateRootSignature(ID3D12Device* device) {}
		virtual void CreateShaders() {}
		virtual void RenderReady(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) {}
		virtual void UpdateShaderVariables() {}
		virtual void DrawPassFrame(ID3D12GraphicsCommandList* commandList) {}

	protected:
		void CreateShader(SPtr<Shader>&& shader);

	public:
		const std::map<ShaderType, SPtr<Shader>>& GetShaders() const { return m_Shaders; }

	protected:	
		SPtr<DirectX12> m_DirectX12;
		ID3D12RootSignature* m_RootSignature = nullptr;
		std::map<ShaderType, SPtr<Shader>> m_Shaders;

	};
}


