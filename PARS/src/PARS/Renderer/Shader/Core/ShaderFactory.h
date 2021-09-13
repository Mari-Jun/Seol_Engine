#pragma once
#include "PARS/Renderer/Shader/Core/Shader.h"	
#include "PARS/Renderer/Shader/Core/RootSignature.h"
#include "PARS/Component/Render/Mesh/MeshComponent.h"

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
		const SPtr<Shader>& GetShader(MeshType type) const;

	private:
		SPtr<DirectX12> m_DirectX12;
		std::unordered_map<std::string, UPtr<class RootSignature>> m_RootSignatures;
	};
}


