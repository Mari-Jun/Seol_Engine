#pragma once

#include "PARS/Core/Core.h"

namespace PARS
{
	enum class ShaderType
	{
		Color
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
		bool BeginDraw(ShaderType type, Args&& ... args)
		{
			auto shaderIter = m_Shaders.find(type);
			auto compIter = m_RenderComponents.find(type);
			if (shaderIter != m_Shaders.end() && compIter != m_RenderComponents.cend())
			{
				const auto& shader = std::reinterpret_pointer_cast<T>(m_Shaders[type]);
				m_DirectX12->GetCommandList()->SetPipelineState(shader->GetPipelineState());
				shader->UpdateShaderVariables(m_DirectX12->GetCommandList(), m_RenderComponents[type], std::forward<Args>(args)...);
				return true;
			}
			return false;
		}
		void Draw(ShaderType type);
		void PrepareToNextDraw();

	public:
		inline static RenderComponentFactory* GetRenderComponentFactory() { return s_Instance; }

		void AddShader(ShaderType type, SPtr<class Shader>&& shader);

		void AddRenderComponent(ShaderType type, const SPtr<class RenderComponent>& component);
		void RemoveRenderComponent(ShaderType type, const SPtr<class RenderComponent>& component);
		void MoveToPrepareComponent(ShaderType type, const SPtr<class RenderComponent>& component);

		SPtr<class Mesh> GetMesh(const std::string& fileName) const;
		void SaveMesh(const std::string& fileName, const SPtr<class Mesh>& mesh);

	private:
		SPtr<class DirectX12> m_DirectX12;
		std::unordered_map<ShaderType, SPtr<class Shader>> m_Shaders;
		std::unordered_map<ShaderType, bool> m_IsShaderUpdate;
		std::unordered_map<ShaderType, std::vector<SPtr<class RenderComponent>>> m_PrepareComponents;
		std::unordered_map<ShaderType, std::vector<SPtr<class RenderComponent>>> m_RenderComponents;
		std::unordered_map<std::string, SPtr<class Mesh>> m_MeshCache;
	};
}


