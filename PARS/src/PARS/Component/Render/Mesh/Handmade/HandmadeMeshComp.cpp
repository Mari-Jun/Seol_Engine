#include "stdafx.h"
#include "PARS/Component/Render/Mesh/Handmade/HandmadeMeshComp.h"
#include "PARS/Component/Render/Mesh/Handmade/HandmadeMeshDF.h"

namespace PARS
{
	HandmadeMeshComponent::HandmadeMeshComponent()
		: MeshComponent("Handmade Mesh Component", MeshType::Handmade)
	{
	}

	void HandmadeMeshComponent::InitializeDetailFunction()
	{
		m_CompDetailFunction = CreateUPtr<HandmadeMeshCompDetailFunction>();
	}

	void HandmadeMeshComponent::Shutdown()
	{
		m_Mesh->Shutdown();
		MeshComponent::Shutdown();
	}

	void HandmadeMeshComponent::RenderReady(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
	{
		m_Mesh->Shutdown();
		MeshComponent::RenderReady(device, commandList);
	}
}