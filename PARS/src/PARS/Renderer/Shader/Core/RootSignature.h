#pragma once
#include "PARS/Renderer/Shader/Core/Shader.h"	

namespace PARS
{
	class ResourceManager;

	struct CBPass
	{};

	class RootSignature
	{
	public:
		RootSignature(const SPtr<ResourceManager>& resourceManager);
		virtual ~RootSignature() = default;

		void Initialize();
		virtual void Shutdown();
		void Update();
		void Draw();
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
		SPtr<ResourceManager> m_ResourceManager;
		SPtr<DirectX12> m_DirectX12;
		ID3D12RootSignature* m_RootSignature = nullptr;
		std::map<ShaderType, SPtr<Shader>> m_Shaders;

	};
}


