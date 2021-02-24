#include "stdafx.h"
#include "PARS/Renderer/DirectX12/DirectX12.h"
#include "PARS/Component/Render/MeshComponent.h"
#include "PARS/Actor/Actor.h"

namespace PARS
{
	MeshComponent::MeshComponent()
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
		auto world = m_Owner.lock()->GetWorldMatrix();
		world.Transpose();
		commandList->SetGraphicsRoot32BitConstants(0, 16, &world, 0);

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
