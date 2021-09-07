#pragma once
#include "PARS/Renderer/Shader/Core/Shader.h"	
#include "PARS/Renderer/Shader/Core/RootSignature.h"
#include "PARS/Component/Light/LightComponent.h"

namespace PARS
{
	class ShaderFactory
	{
	public:
		ShaderFactory(const SPtr<DirectX12>& directX);
		~ShaderFactory() = default;
		
		void Initialize();
		void Shutdown();
		void Update();
		void Draw();
		void PrepareToNextDraw();

	private:
		void CreateRootSignatures();

	public:
		const SPtr<Shader>& GetShader(RenderType type) const;

	private:
		SPtr<DirectX12> m_DirectX12;
		std::unordered_map<std::string, UPtr<RootSignature>> m_RootSignatures;
	};
}


