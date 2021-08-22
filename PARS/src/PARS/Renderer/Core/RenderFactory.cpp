#include "stdafx.h"
#include "PARS/Renderer/Core/RenderFactory.h"
#include "PARS/Core/Window.h"
#include "PARS/Renderer/Shader/ColorShader.h"
#include "PARS/Actor/Actor.h"

namespace PARS
{
	RenderFactory::RenderFactory(const SPtr<DirectX12>& directX)
		: m_DirectX12(directX)
	{
		
	}

	bool RenderFactory::Initialize()
	{
		m_Viewports.emplace_back(CreateSPtr<Viewport>());

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
		m_RootSignatures.clear();

		m_RenderCompFactory->Shutdown();
	}

	void RenderFactory::RenderReady()
	{
		for (const auto& viewport : m_Viewports)
		{
			const auto& camera = viewport->GetCameraOwner().lock();

			if (viewport->IsChangeViewport())
			{
				const auto& directX = DirectX12::GetDirectX12();
				if (directX != nullptr)
				{
					directX->SetViewAndScissor(viewport->GetLeft(), viewport->GetTop(),
						viewport->GetWidth(), viewport->GetHeight());
				}

				if (camera != nullptr)
				{
					camera->ChangeProjectionInfo();
				}
				viewport->ChangedViewport();
			}

			if (camera != nullptr && camera->IsUpdateProjection())
			{
				camera->UpdateProjection(viewport->GetWidth(), viewport->GetHeight());
			}

		}

		m_RenderCompFactory->RenderReady();
	}

	void RenderFactory::Draw()
	{
		auto commandList = m_DirectX12->GetCommandList();
		commandList->SetGraphicsRootSignature(m_RootSignatures["Default"]);

		Mat4 viewProj;
		for (const auto& camera : m_CameraComps)
		{
			if (camera->IsActive())
			{
				CBColorPass cbPass;

				viewProj = camera->GetViewMatrix();
				viewProj *= camera->GetProjection();
				viewProj.Transpose();

				const Vec3& eyePos = camera->GetOwner().lock()->GetPosition();

				cbPass.m_ViewProj = viewProj;
				cbPass.m_EyePos = eyePos;

				std::vector<LightCB> lights;
				LightCount lightCount;
				for (const auto& light : m_LightComps)
				{
					lights.push_back(light->GetLightCB());
					lightCount.AddLightCount(light->GetLightType());
				}

				cbPass.m_LightCount = lightCount;
				cbPass.m_AmbientLight = { 0.25f, 0.25f, 0.25f, 1.0f };
				if (!lights.empty())
					*cbPass.m_Lights = *lights.data();
				else
					cbPass.m_AmbientLight = { 1.0f,  1.0f, 1.0f, 1.0f };

				if (m_RenderCompFactory->BeginDraw<ColorShader>(ShaderType::Color, RenderType::Mesh, cbPass))
				{
					m_RenderCompFactory->Draw(ShaderType::Color, RenderType::Mesh);
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

	void RenderFactory::AddCameraComponent(const SPtr<CameraComponent>& camera)
	{
		m_CameraComps.push_back(camera);

		//���� viewport�� 1���̴�. ���� main viewport�� �÷��̾� ��Ʈ�ѷ��� �����ϴ� camera�� �������. <�ӽ�>
		m_Viewports[0]->SetCamera(camera);
	}

	void RenderFactory::RemoveCameraComponent(const SPtr<CameraComponent>& camera)
	{
		auto iter = std::find_if(m_CameraComps.begin(), m_CameraComps.end(),
			[&camera](const SPtr<CameraComponent>& comp)
			{return camera == comp; });
		if (iter != m_CameraComps.end())
		{
			m_CameraComps.erase(iter);
		}
	}

	void RenderFactory::AddLightComponent(const SPtr<LightComponent>& light)
	{
		m_LightComps.push_back(light);
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

	void RenderFactory::UpdateProjection(float left, float top, float width, float height)
	{

	}

	RenderFactory* RenderFactory::s_Instance = nullptr;
}