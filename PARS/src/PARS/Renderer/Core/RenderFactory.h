#pragma once
#include "PARS/Renderer/Core/Viewport.h"
#include "PARS/Renderer/Core/RenderComponentFactory.h"
#include "PARS/Component/Camera/CameraComponent.h"
#include "PARS/Component/Light/LightComponent.h"
#include "PARS/Renderer/Shader/Core/Shader.h"

namespace PARS
{
	class RenderFactory
	{
	private:
		static RenderFactory* s_Instance;

	public:
		RenderFactory(const SPtr<DirectX12>& directX);
		~RenderFactory() = default;
		
		bool Initialize();
		void Shutdown();
		void RenderReady();
		void Draw();
		void PrepareToNextDraw();
		
	private:
		bool CreateDefaultRootSignatures();
		void CreateShaders();
		void CreateShader(std::string&& signatureType, ShaderType type, SPtr<Shader>&& shader);

	public:
		const SPtr<Viewport>& GetViewport(int index) { return m_Viewports[index]; }

		void AddCameraComponent(const SPtr<CameraComponent>& camera);
		void RemoveCameraComponent(const SPtr<CameraComponent>& camera);

		void AddLightComponent(const SPtr<LightComponent>& light);
		void RemoveLightComponent(const SPtr<LightComponent>& light);

		void UpdateProjection(float left, float top, float width, float height);

		inline static RenderFactory* GetRenderFactory() { return s_Instance; }

	private:
		SPtr<DirectX12> m_DirectX12;
		std::vector<SPtr<Viewport>> m_Viewports;
		UPtr<RenderComponentFactory> m_RenderCompFactory;
		std::unordered_map<std::string, ID3D12RootSignature*> m_RootSignatures;
		std::vector<SPtr<CameraComponent>> m_CameraComps;
		std::list<SPtr<LightComponent>> m_LightComps;
	};
}


