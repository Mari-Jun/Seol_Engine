#pragma once

#include "PARS/Core/Core.h"

namespace PARS
{
	enum class ShaderType
	{
		Color
	};

	enum class RenderType
	{
		Mesh
	};

	enum class RenderState
	{
		Ready,
		Render,
		Invisible
	};

	class RenderComponentFactory
	{
	private:
		static RenderComponentFactory* s_Instance;

	public:
		RenderComponentFactory(const SPtr<class DirectX12>& directX);
		~RenderComponentFactory() = default;

		bool Initialize();
		void Shutdown(); 
		void RenderReady();
		template<typename T, typename ... Args>
		bool BeginDraw(ShaderType sType, RenderType rType, Args&& ... args)
		{
			auto shaderIter = m_Shaders.find(sType);
			auto compIter = m_RenderComponents.find(rType);
			if (shaderIter != m_Shaders.end() && compIter != m_RenderComponents.cend())
			{
				const auto& shader = std::reinterpret_pointer_cast<T>(m_Shaders[sType]);
				m_DirectX12->GetCommandList()->SetPipelineState(shader->GetPipelineState());
				shader->UpdateShaderVariables(m_DirectX12->GetCommandList(), m_RenderComponents[rType], std::forward<Args>(args)...);
				return true;
			}
			return false;
		}
		void Draw(ShaderType sType, RenderType rType);
		void PrepareToNextDraw();

	public:
		inline static RenderComponentFactory* GetRenderComponentFactory() { return s_Instance; }

		void AddShader(ShaderType type, SPtr<class Shader>&& shader);

		void AddRenderComponent(RenderType type, const SPtr<class RenderComponent>& component);
		void AddPrepareComponent(RenderType type, const SPtr<class RenderComponent>& component);
		void RemoveRenderComponent(RenderType type, const SPtr<class RenderComponent>& component);

		const SPtr<class Mesh>& GetMesh(const std::string& fileName) const;
		void SaveMesh(const std::string& fileName, const SPtr<class Mesh>& mesh);

	private:
		void UpdateShaderDueToRender(RenderType renderType);


	private:
		struct ShaderUpdateInfo
		{
			ShaderType m_ShaderType;
			RenderType m_RenderType;
		};

	private:
		SPtr<class DirectX12> m_DirectX12;
		std::unordered_map<ShaderType, SPtr<class Shader>> m_Shaders;
		std::vector<ShaderUpdateInfo> m_ShaderUpdateInfos;
		std::unordered_map<RenderType, std::vector<SPtr<class RenderComponent>>> m_PrepareComponents;
		std::unordered_map<RenderType, std::vector<SPtr<class RenderComponent>>> m_RenderComponents;
		std::unordered_map<std::string, SPtr<class Mesh>> m_MeshCache;
	};
}


