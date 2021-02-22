#pragma once

#include "PARS/Renderer/Core/RenderComponentFactory.h"
#include "PARS/Component/Camera/CameraComponent.h"
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
		void BeginDraw();
		void Draw();
		void PrepareToNextDraw();
		
	private:
		bool CreateDefaultRootSignatures();
		void CreateShaders();
		void CreateShader(std::string&& signatureType, ShaderType type, UPtr<Shader>&& shader);

	public:
		void AddCameraComponent(CameraComponent::CameraType type, const SPtr<CameraComponent>& camera);
		void RemoveCameraComponent(CameraComponent::CameraType type, const SPtr<CameraComponent>& camera);

		inline static RenderFactory* GetRenderFactory() { return s_Instance; }

	private:
		SPtr<DirectX12> m_DirectX12;
		UPtr<RenderComponentFactory> m_RenderCompFactory;
		std::unordered_map<std::string, ID3D12RootSignature*> m_RootSignatures;
		std::unordered_map<ShaderType, UPtr<Shader>> m_Shaders;
		std::unordered_map<CameraComponent::CameraType, std::vector<SPtr<CameraComponent>>> m_CameraComps;
	};
}


