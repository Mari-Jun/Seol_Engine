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

		m_AssetStore = CreateUPtr<AssetStore>(m_DirectX12);
		if (!m_AssetStore->Initialize())
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
			if (iter->second.m_RootSignature != nullptr)
			{
				iter->second.m_RootSignature->Release();
				for (const auto& [type, shader] : iter->second.m_Shaders)
				{
					shader->Shutdown();
				}
				iter->second.m_Shaders.clear();
			}
		}
		m_RootSignatures.clear();

		m_AssetStore->Shutdown();
	}

	void RenderFactory::Update()
	{
		UpdateViewport();
		for (const auto& [string, signature] : m_RootSignatures)
		{
			for (const auto& [type, shader] : signature.m_Shaders)
			{
				shader->Update(m_DirectX12->GetDevice(), m_DirectX12->GetCommandList());
			}
		}
	}

	void RenderFactory::UpdateViewport()
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
	}

	void RenderFactory::Draw()
	{
		auto commandList = m_DirectX12->GetCommandList();

		for (const auto& [string, signature] : m_RootSignatures)
		{
			commandList->SetGraphicsRootSignature(signature.m_RootSignature);
			for (const auto& [type, shader] : signature.m_Shaders)
			{
				shader->Draw(commandList);
			}
		}
	}

	void RenderFactory::PrepareToNextDraw()
	{
		for (const auto& [string, signature] : m_RootSignatures)
		{
			for (const auto& [type, shader] : signature.m_Shaders)
			{
				shader->PrepareToNextDraw();
			}
		}
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
		m_RootSignatures.insert({ "Default", {defaultRootSignature} });

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
		CreateShader("Default", CreateSPtr<ColorShader>(m_DirectX12));		
	}

	void RenderFactory::CreateShader(std::string&& signatureType, SPtr<Shader>&& shader)
	{
		auto& signature = m_RootSignatures[signatureType];
			
		if (signature.m_RootSignature != nullptr && shader->Initialize(signature.m_RootSignature))
		{
			signature.m_Shaders[shader->GetShaderType()] = shader;
		}
	}

	const SPtr<Shader>& RenderFactory::GetShader(RenderType type) const
	{
		switch (type)
		{
		case PARS::RenderType::Mesh: 
			return m_RootSignatures.at("Default").m_Shaders.at(ShaderType::Color);
		default:
			return nullptr;
		}
	}

	void RenderFactory::AddRenderComponent(RenderType type, const SPtr<RenderComponent>& component)
	{
		AddPrepareComponent(type, component);
		const auto& shader = GetShader(type);
		if (shader != nullptr)
			shader->AddRenderComponent(component);
	}

	void RenderFactory::AddPrepareComponent(RenderType type, const SPtr<class RenderComponent>& component)
	{
		RenderState state = component->GetRenderState();
		if (state == RenderState::Ready || state == RenderState::Changed)
		{
			const auto& shader = GetShader(type);
			if (shader != nullptr)
				shader->AddPrepareComponent(component);
		}
	}

	void RenderFactory::RemoveRenderComponent(RenderType type, const SPtr<RenderComponent>& component)
	{
		const auto& shader = GetShader(type);
		if (shader != nullptr)
			shader->RemoveRenderComponent(component);
	}


	void RenderFactory::AddCameraComponent(const SPtr<CameraComponent>& camera)
	{
		m_CameraComps.push_back(camera);

		//아직 viewport는 1개이다. 따라서 main viewport에 플레이어 컨트롤러가 제어하는 camera가 담겨진다. <임시>
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

	RenderFactory* RenderFactory::s_Instance = nullptr;
}