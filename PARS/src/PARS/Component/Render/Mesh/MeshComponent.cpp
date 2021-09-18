#include "stdafx.h"
#include "PARS/Renderer/DirectX12/DirectX12.h"
#include "PARS/Renderer/Core/RenderFactory.h"
#include "PARS/Component/Render/Mesh/MeshComponent.h"
#include "PARS/Component/Render/Mesh/MeshDetailFunction.h"
#include "PARS/Component/Render/Material/Material.h"
#include "PARS/Renderer/Core/RenderItem.h"
#include "PARS/Actor/Actor.h"

namespace PARS
{
	MeshComponent::MeshComponent(const std::string& name, MeshType type)
		: Component(name)
		, m_MeshType(type)
	{

	}

	void MeshComponent::Initialize()
	{
	}

	void MeshComponent::InitializeDetailFunction()
	{
		m_CompDetailFunction = CreateUPtr<MeshCompDetailFunction>();
	}

	void MeshComponent::Shutdown()
	{
		RenderFactory::GetRenderFactory()->RemoveMeshCompForDraw(std::reinterpret_pointer_cast<MeshComponent>(shared_from_this()));
		m_Mesh = nullptr;
		m_Materials.clear();
	}

	void MeshComponent::AddToRenderFactory()
	{
		RenderFactory::GetRenderFactory()->AddMeshCompForDraw(std::reinterpret_pointer_cast<MeshComponent>(shared_from_this()));
	}

	void MeshComponent::RemoveFromRenderFactory()
	{
		RenderFactory::GetRenderFactory()->RemoveMeshCompForDraw(std::reinterpret_pointer_cast<MeshComponent>(shared_from_this()));
	}


	void MeshComponent::Draw(ID3D12GraphicsCommandList* commandList)
	{
		if (m_Mesh != nullptr)
		{
			m_Mesh->BeginDraw(commandList);
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
