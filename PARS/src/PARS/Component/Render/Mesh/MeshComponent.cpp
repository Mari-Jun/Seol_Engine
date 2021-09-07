#include "stdafx.h"
#include "PARS/Renderer/DirectX12/DirectX12.h"
#include "PARS/Component/Render/Mesh/MeshComponent.h"
#include "PARS/Component/Render/Mesh/MeshDetailFunction.h"
#include "PARS/Actor/Actor.h"

namespace PARS
{
	MeshComponent::MeshComponent(const std::string& name, RenderType type)
		: RenderComponent(name, type)
	{

	}

	void MeshComponent::Initialize()
	{
		RenderComponent::Initialize();
	}

	void MeshComponent::InitializeDetailFunction()
	{
		m_CompDetailFunction = CreateUPtr<MeshCompDetailFunction>();
	}

	void MeshComponent::Shutdown()
	{
		m_Mesh = nullptr;
		RenderComponent::Shutdown();
	}

	void MeshComponent::Draw(ID3D12GraphicsCommandList* commandList)
	{
		if (m_Mesh != nullptr)
		{
			m_Mesh->Draw(commandList);
		}
	}

	void MeshComponent::RenderReady(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
	{
		if (m_Mesh != nullptr)
		{
			m_Mesh->SetBuffer(device, commandList);
		}
	}

	void MeshComponent::ReleaseUploadBuffers()
	{
		if (m_Mesh != nullptr)
		{
			m_Mesh->ReleaseUploadBuffers();
		}
	}
}
