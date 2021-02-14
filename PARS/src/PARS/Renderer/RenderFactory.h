#pragma once

#include "PARS/Renderer/Shader/Core/Shader.h"

namespace PARS
{
	class RenderFactory
	{
	private:
		static RenderFactory* s_Instance;

	public:
		RenderFactory(SPtr<DirectX12>& directX);
		~RenderFactory() = default;
		
		bool Initialize();
		void Shutdown();

		void DrawDefualtShader();
		
	private:
		bool CreateRootSignatures();
		void CreateShaders();
		void CreateShader(std::string&& signatureType, std::string&& shaderName, UPtr<Shader>&& shader);

	public:
		inline static RenderFactory* GetRenderFactory() { return s_Instance; }

	private:
		SPtr<DirectX12> m_DirectX12;
		std::unordered_map<std::string, ID3D12RootSignature*> m_RootSignatures;
		std::unordered_map<std::string, UPtr<Shader>> m_Shaders;
	};
}


