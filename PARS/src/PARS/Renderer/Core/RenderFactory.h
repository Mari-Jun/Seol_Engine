#pragma once
#include "PARS/Renderer/Core/Viewport.h"
#include "PARS/Component/Render/RenderComponent.h"
#include "PARS/Component/Camera/CameraComponent.h"
#include "PARS/Component/Light/LightComponent.h"
#include "PARS/Renderer/Shader/Core/Shader.h"
#include "PARS/Renderer/Shader/Core/ShaderFactory.h"

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
		void Update();
		void Draw();
		void PrepareToNextDraw();
		
	private:
		void UpdateViewport();

	public:
		const SPtr<Viewport>& GetViewport(int index) { return m_Viewports[index]; }

		inline static RenderFactory* GetRenderFactory() { return s_Instance; }

	private:
		UPtr<ShaderFactory> m_ShaderFactory;
		std::vector<SPtr<Viewport>> m_Viewports;

	private:
		std::vector<SPtr<CameraComponent>> m_CameraComps;
		std::list<SPtr<LightComponent>> m_LightComps;

	public:
		void AddRenderComponent(RenderType type, const SPtr<RenderComponent>& component);
		void AddPrepareComponent(RenderType type, const SPtr<RenderComponent>& component);
		void RemoveRenderComponent(RenderType type, const SPtr<RenderComponent>& component);

		void AddCameraComponent(const SPtr<CameraComponent>& camera);
		void RemoveCameraComponent(const SPtr<CameraComponent>& camera);

		void AddLightComponent(const SPtr<LightComponent>& light);
		void RemoveLightComponent(const SPtr<LightComponent>& light);

		const std::vector<SPtr<CameraComponent>>& GetCameraComps() const { return m_CameraComps; }
		const std::list<SPtr<LightComponent>>& GetLightComps() const { return m_LightComps; }

	};
}


