#include "stdafx.h"
#include "PARS/Renderer/Core/RenderFactory.h"
#include "PARS/Core/Window.h"
#include "PARS/Renderer/Shader/ColorShader.h"

namespace PARS
{
	RenderFactory::RenderFactory(const SPtr<DirectX12>& directX)
		: m_DirectX12(directX)
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
		for (auto iter = m_Shaders.begin(); iter != m_Shaders.end(); ++iter)
		{
			iter->second->Shutdown();
		}

		for (auto iter = m_RootSignatures.begin(); iter != m_RootSignatures.end(); ++iter)
		{
			if (iter->second != nullptr)
			{
				iter->second->Release();
			}
		}

		m_RenderCompFactory->Shutdown();
	}

	void RenderFactory::BeginDraw()
	{
		m_RenderCompFactory->BeginDraw();
	}

	void RenderFactory::Draw()
	{
		auto commandList = m_DirectX12->GetCommandList();
		commandList->SetGraphicsRootSignature(m_RootSignatures["Default"]);

		/*Vec3 eye(0.0f, 0.0f, -0.1f);
		Vec3 target = Vec3::Zero;
		Vec3 up = Vec3::AxisY;

		Mat4 camera = Mat4::LookAt(eye, target, up);
		static float aspect = static_cast<float>(Window::GetWindowInfo()->m_Width) / static_cast<float>(Window::GetWindowInfo()->m_Height);
		Mat4 p = Mat4::Perspective(Math::ToRadians(90.0f), aspect, 1.0f, 500.0f);

		Mat4 viewProj = camera * p;
		viewProj.Transpose();*/

		Mat4 viewProj;

		commandList->SetGraphicsRoot32BitConstants(0, 16, &viewProj, 0);

		m_Shaders[ShaderType::Color]->Draw();
		m_RenderCompFactory->Draw(ShaderType::Color);
	}

	void RenderFactory::PrepareToNextDraw()
	{
		m_RenderCompFactory->PrepareToNextDraw();
	}

	bool RenderFactory::CreateDefaultRootSignatures()
	{
		ID3D12RootSignature* defaultRootSignature = nullptr;

		D3D12_ROOT_PARAMETER rootParameter[2];
		rootParameter[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
		rootParameter[0].Constants.Num32BitValues = 16;
		rootParameter[0].Constants.ShaderRegister = 0;
		rootParameter[0].Constants.RegisterSpace = 0;
		rootParameter[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
		rootParameter[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
		rootParameter[1].Constants.Num32BitValues = 32;
		rootParameter[1].Constants.ShaderRegister = 1;
		rootParameter[1].Constants.RegisterSpace = 0;
		rootParameter[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;

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
		CreateShader("Default", ShaderType::Color, CreateUPtr<ColorShader>(m_DirectX12));		
	}

	void RenderFactory::CreateShader(std::string&& signatureType, ShaderType type, UPtr<Shader>&& shader)
	{
		if (m_RootSignatures[signatureType] !=nullptr && shader->Initialize(m_RootSignatures[signatureType]))
		{
			m_Shaders.insert({ type, std::move(shader) });
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

	RenderFactory* RenderFactory::s_Instance = nullptr;
}