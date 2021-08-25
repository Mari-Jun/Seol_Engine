#include "stdafx.h"
#include "PARS/Renderer/DirectX12/DirectX12.h"
#include "PARS/Component/Render/Mesh/MeshComponent.h"
#include "PARS/Component/Render/Mesh/MeshDetailFunction.h"
#include "PARS/Actor/Actor.h"

namespace PARS
{
	MeshComponent::MeshComponent(const std::string& name)
		: RenderComponent(name, RenderType::Mesh)
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
