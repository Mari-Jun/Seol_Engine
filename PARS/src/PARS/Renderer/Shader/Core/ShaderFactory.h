#pragma once
#include "PARS/Renderer/Shader/Core/Shader.h"	
#include "PARS/Renderer/Shader/Core/RootSignature.h"
#include "PARS/Component/Render/Mesh/MeshComponent.h"

namespace PARS
{
	class ResourceManager;

	class ShaderFactory
	{
	public:
		ShaderFactory(const SPtr<ResourceManager>& resourceManager);
		~ShaderFactory() = default;
		
		void Initialize();
		void Shutdown();
		void Update();
		void Draw();
		void PrepareToNextDraw();

	private:
		void CreateRootSignatures(const SPtr<ResourceManager>& resourceManager);

	public:
		const SPtr<Shader>& GetShader(MeshType type) const;

	private:
		std::unordered_map<std::string, UPtr<class RootSignature>> m_RootSignatures;
	};
}


