#pragma once

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
		template<typename Component, typename Type>
		void AddWorldComponent(Type type, const Component& comp)
		{

			std::is_same(Component, CameraComponent)
		}

		template<typename Component, typename Type, typename Data>
		void AddWorldComponent(Type type, const Component& comp, Data& data)
		{

		}


		void AddCameraComponent(CameraComponent::CameraType type, const SPtr<CameraComponent>& camera);
		void RemoveCameraComponent(CameraComponent::CameraType type, const SPtr<CameraComponent>& camera);

		void SetProjection(const Mat4& projection) { m_Projection = projection; }

		void AddLightComponent(const SPtr<LightComponent>& light);
		void RemoveLightComponent(const SPtr<LightComponent>& light);

		inline static RenderFactory* GetRenderFactory() { return s_Instance; }

	private:
		SPtr<DirectX12> m_DirectX12;
		UPtr<RenderComponentFactory> m_RenderCompFactory;
		std::unordered_map<std::string, ID3D12RootSignature*> m_RootSignatures;
		std::unordered_map<CameraComponent::CameraType, std::vector<SPtr<CameraComponent>>> m_CameraComps;
		std::list<SPtr<LightComponent>> m_LightComps;

	private:
		Mat4 m_Projection;
	};
}


