#pragma once
#include "PARS/Renderer/Shader/Core/Shader.h"
#include "PARS/Renderer/Shader/Core/ShaderFactory.h"

namespace PARS
{
	class ResourceManager;
	class ImGuiLayer;
	class CameraComponent;
	class LightComponent;

	class RenderFactory
	{
	private:
		static RenderFactory* s_Instance;

	public:
		RenderFactory(const SPtr<DirectX12>& directX);
		~RenderFactory() = default;
		
		bool Initialize();
		void Shutdown();
		void Update();
		void Draw();
		void PrepareToNextDraw();
		
	private:
		void UpdateViewport();

	public:
		const SPtr<class ImGuiLayer>& CreateImGui();

		inline static RenderFactory* GetRenderFactory() { return s_Instance; }

	private:
		SPtr<ResourceManager> m_ResourceManager;
		SPtr<ImGuiLayer> m_ImGuiLayer;
		UPtr<ShaderFactory> m_ShaderFactory;

	private:
		std::vector<SPtr<CameraComponent>> m_CameraComps;
		std::list<SPtr<LightComponent>> m_LightComps;

	public:
		void AddMeshCompForDraw(const SPtr<class MeshComponent>& meshComp);
		void RemoveMeshCompForDraw(const SPtr<class MeshComponent>& meshComp);

		void AddCameraComponent(const SPtr<CameraComponent>& camera);
		void RemoveCameraComponent(const SPtr<CameraComponent>& camera);

		void AddLightComponent(const SPtr<LightComponent>& light);
		void RemoveLightComponent(const SPtr<LightComponent>& light);

		const std::vector<SPtr<CameraComponent>>& GetCameraComps() const { return m_CameraComps; }
		const std::list<SPtr<LightComponent>>& GetLightComps() const { return m_LightComps; }
		SPtr<CameraComponent> GetCameraComp(const std::string& ownerName);

	};
}


