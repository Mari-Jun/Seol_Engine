#include "stdafx.h"
#include "PARS/Renderer/DirectX12/DirectX12.h"
#include "PARS/Component/Render/Mesh/MeshComponent.h"
#include "PARS/Component/Render/Mesh/MeshDetailFunction.h"
#include "PARS/Actor/Actor.h"

namespace PARS
{
	MeshComponent::MeshComponent(const std::string& name)
		: RenderComponent(name)
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
		RenderComponent::Shutdown();
		//Mesh는 자동으로 Cache에 저장되기 때문에 여기서 Shutdown을 하지 않음.
	}

	void MeshComponent::Draw(ID3D12GraphicsCommandList* commandList)
	{
		m_Mesh->Draw(commandList);
	}

	void MeshComponent::RenderReady(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
	{
		m_Mesh->SetBuffer(device, commandList);
	}

	void MeshComponent::ReleaseUploadBuffers()
	{
		m_Mesh->ReleaseUploadBuffers();
	}
}
