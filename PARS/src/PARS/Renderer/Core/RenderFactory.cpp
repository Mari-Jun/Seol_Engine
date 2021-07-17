#include "stdafx.h"
#include "PARS/Renderer/Core/RenderFactory.h"
#include "PARS/Core/Window.h"
#include "PARS/Renderer/Shader/ColorShader.h"
#include "PARS/Actor/Actor.h"

namespace PARS
{
	RenderFactory::RenderFactory(const SPtr<DirectX12>& directX)
		: m_DirectX12(directX)
		, m_Projection(Mat4::Identity)
	{
		
	}

	bool RenderFactory::Initialize()
	{
		m_RenderCompFactory = CreateUPtr<RenderComponentFactory>(m_DirectX12);
		if (!m_RenderCompFactory->Initialize())
		{
			PARS_ERROR("Could not initialize RenderComponentFactory");
			return false;
		}

		if (!CreateDefaultRootSignatures()) return false;

		CreateShaders();

		s_Instance = this;

		return true;
	}

	void RenderFactory::Shutdown()
	{
		for (auto iter = m_RootSignatures.begin(); iter != m_RootSignatures.end(); ++iter)
		{
			if (iter->second != nullptr)
			{
				iter->second->Release();
			}
		}

		m_RenderCompFactory->Shutdown();
	}

	void RenderFactory::RenderReady()
	{
		m_RenderCompFactory->RenderReady();
	}

	void RenderFactory::Draw()
	{
		auto commandList = m_DirectX12->GetCommandList();
		commandList->SetGraphicsRootSignature(m_RootSignatures["Default"]);

		Mat4 viewProj;

		auto cameraIter = m_CameraComps.find(CameraComponent::CameraType::Default);
		if (cameraIter != m_CameraComps.cend())
		{
			for (const auto& camera : m_CameraComps[CameraComponent::CameraType::Default])
			{
				if (camera->IsActive())
				{
					viewProj = camera->GetViewMatrix();
					viewProj *= m_Projection;
					viewProj.Transpose();

					const Vec3& eyePos = camera->GetOwner().lock()->GetPosition();

					std::vector<LightCB> lights;
					LightCount lightCount;
					for (const auto& light : m_LightComps)
					{
						lights.push_back(light->GetLightCB());
						lightCount.AddLightCount(light->GetLightType());
					}

					if (m_RenderCompFactory->BeginDraw<ColorShader>(ShaderType::Color, RenderType::Mesh, CBColorPass{ viewProj, eyePos, 0.0f, lightCount, 0.0f, *lights.data() }))
					{
						m_RenderCompFactory->Draw(ShaderType::Color, RenderType::Mesh);
					}
				}
			}
		}
	}

	void RenderFactory::PrepareToNextDraw()
	{
		m_RenderCompFactory->PrepareToNextDraw();
	}

	bool RenderFactory::CreateDefaultRootSignatures()
	{
		ID3D12RootSignature* defaultRootSignature = nullptr;

		D3D12_ROOT_PARAMETER rootParameter[2];
		rootParameter[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
		rootParameter[0].Descriptor.ShaderRegister = 0;
		rootParameter[0].Descriptor.RegisterSpace = 0;
		rootParameter[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
		rootParameter[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
		rootParameter[1].Descriptor.ShaderRegister = 1;
		rootParameter[1].Descriptor.RegisterSpace = 0;
		rootParameter[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

		D3D12_ROOT_SIGNATURE_DESC rsDesc;
		rsDesc.NumParameters = _countof(rootParameter);
		rsDesc.pParameters = rootParameter;
		rsDesc.NumStaticSamplers = 0;
		rsDesc.pStaticSamplers = nullptr;
		rsDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

		ID3DBlob* signatureBlob = nullptr;
		ID3DBlob* errorBlob = nullptr;
		HRESULT result = D3D12SerializeRootSignature(&rsDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob, &errorBlob);

		if (errorBlob != nullptr)
		{
			OutputDebugStringA((char*)errorBlob->GetBufferPointer());
		}
		if (FAILED(result)) return false;

		auto device = m_DirectX12->GetDevice();
		device->CreateRootSignature(0, signatureBlob->GetBufferPointer(), signatureBlob->GetBufferSize(), IID_PPV_ARGS(&defaultRootSignature));
		m_RootSignatures.insert({ "Default", defaultRootSignature });

		if (signatureBlob != nullptr)
		{
			signatureBlob->Release();
		}
		if (errorBlob != nullptr)
		{
			errorBlob->Release();
		}

		return true;
	}

	void RenderFactory::CreateShaders()
	{
		CreateShader("Default", ShaderType::Color, CreateSPtr<ColorShader>(m_DirectX12));		
	}

	void RenderFactory::CreateShader(std::string&& signatureType, ShaderType type, SPtr<Shader>&& shader)
	{
		if (m_RootSignatures[signatureType] !=nullptr && shader->Initialize(m_RootSignatures[signatureType]))
		{
			m_RenderCompFactory->AddShader(type, std::move(shader));
		}
	}

	void RenderFactory::AddCameraComponent(CameraComponent::CameraType type, const SPtr<CameraComponent>& camera)
	{
		auto iter = m_CameraComps.emplace(type, std::vector<SPtr<CameraComponent>>{camera});
		if (!iter.second)
		{
			iter.first->second.emplace_back(camera);
		}
	}

	void RenderFactory::RemoveCameraComponent(CameraComponent::CameraType type, const SPtr<CameraComponent>& camera)
	{
		auto rComp = m_CameraComps.find(type);
		if (rComp != m_CameraComps.end())
		{
			auto iter = std::find_if(rComp->second.begin(), rComp->second.end(),
				[&camera](const SPtr<CameraComponent>& comp)
				{return camera == comp; });
			if (iter != rComp->second.end())
			{
				rComp->second.erase(iter);
				if (rComp->second.empty())
				{
					m_CameraComps.erase(type);
				}
			}
		}
	}

	void RenderFactory::AddLightComponent(const SPtr<LightComponent>& light)
	{
		m_LightComps.emplace_back(light);
	}

	void RenderFactory::RemoveLightComponent(const SPtr<LightComponent>& light)
	{
		auto iter = std::find_if(m_LightComps.begin(), m_LightComps.end(),
			[&light](const SPtr<LightComponent>& comp)
			{return light == comp; });
		if (iter != m_LightComps.end())
		{
			m_LightComps.erase(iter);
		}
	}

	RenderFactory* RenderFactory::s_Instance = nullptr;
}