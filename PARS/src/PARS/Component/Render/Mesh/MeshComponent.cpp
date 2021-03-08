#include "stdafx.h"
#include "PARS/Renderer/DirectX12/DirectX12.h"
#include "PARS/Component/Render/Mesh/MeshComponent.h"
#include "PARS/Actor/Actor.h"

namespace PARS
{
	MeshComponent::MeshComponent()
		: RenderComponent()
	{
		
	}

	void MeshComponent::Initialize()
	{
		RenderComponent::Initialize();
	}

	void MeshComponent::Shutdown()
	{
		RenderComponent::Shutdown();
		m_Mesh->Shutdown();
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
