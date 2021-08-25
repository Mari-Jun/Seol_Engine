#pragma once
#include "PARS/Renderer/Core/Viewport.h"
#include "PARS/Renderer/Core/AssetStore.h"
#include "PARS/Component/Render/RenderComponent.h"
#include "PARS/Component/Camera/CameraComponent.h"
#include "PARS/Component/Light/LightComponent.h"
#include "PARS/Renderer/Shader/Core/Shader.h"

namespace PARS
{
	struct RootSignature
	{
		ID3D12RootSignature* m_RootSignature;
		std::map<ShaderType, SPtr<Shader>> m_Shaders;
	};

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
		bool CreateDefaultRootSignatures();
		void CreateShaders();
		void CreateShader(std::string&& signatureType, SPtr<Shader>&& shader);

		void UpdateViewport();

	private:
		const SPtr<Shader>& GetShader(RenderType type) const;

	public:
		const SPtr<Viewport>& GetViewport(int index) { return m_Viewports[index]; }

		inline static RenderFactory* GetRenderFactory() { return s_Instance; }

	private:
		SPtr<DirectX12> m_DirectX12;
		UPtr<AssetStore> m_AssetStore;
		std::vector<SPtr<Viewport>> m_Viewports;
		std::unordered_map<std::string, RootSignature> m_RootSignatures;

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


