#include "stdafx.h"
#include "PARS/Component/Render/Mesh/Handmade/HandmadeMeshComp.h"
#include "PARS/Component/Render/Mesh/Handmade/HandmadeMeshDF.h"

namespace PARS
{
	HandmadeMeshComponent::HandmadeMeshComponent()
		: MeshComponent("Handmade Mesh Component")
	{
	}

	void HandmadeMeshComponent::InitializeDetailFunction()
	{
		m_CompDetailFunction = CreateUPtr<HandmadeMeshCompDetailFunction>();
	}

	void HandmadeMeshComponent::Shutdown()
	{
		MeshComponent::Shutdown();
		m_Mesh->Shutdown();
	}

	void HandmadeMeshComponent::RenderReady(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
	{
		m_Mesh->Shutdown();
		MeshComponent::RenderReady(device, commandList);
	}
}