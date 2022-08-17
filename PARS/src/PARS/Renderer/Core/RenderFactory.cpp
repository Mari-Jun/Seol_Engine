#include "stdafx.h"
#include "PARS/ImGui/ImGuiLayer.h"
#include "PARS/Renderer/Core/ResourceManager.h"
#include "PARS/Renderer/Core/RenderFactory.h"
#include "PARS/Component/Render/Mesh/MeshComponent.h"
#include "PARS/Component/Camera/CameraComponent.h"
#include "PARS/Component/Light/LightComponent.h"
#include "PARS/Actor/Actor.h"
#include "PARS/Core/Window.h"

namespace PARS
{
	RenderFactory::RenderFactory(const SPtr<DirectX12>& directX)
	{
		m_ResourceManager = CreateSPtr<ResourceManager>(directX);
		//m_ImGuiLayer = CreateSPtr<ImGuiLayer>(directX);
		m_ShaderFactory = CreateUPtr<ShaderFactory>(m_ResourceManager);
	}

	bool RenderFactory::Initialize()
	{
		s_Instance = this;
		m_ResourceManager->Initialize();

	/*	m_ResourceManager->CreateSRVHeap([this](ID3D12DescriptorHeap* heap)
			{
				m_ImGuiLayer->InitFromNewSRVHeap(heap);
			});*/

		//m_Viewports.emplace_back(CreateSPtr<Viewport>());

		m_ShaderFactory->Initialize();
		return true;
	}

	void RenderFactory::Shutdown()
	{
		m_ShaderFactory->Shutdown();
		m_ResourceManager->Shutdown();
	}

	void RenderFactory::Update()
	{

	/*	m_ResourceManager->CreateSRVHeap([this](ID3D12DescriptorHeap* heap)
			{
				m_ImGuiLayer->InitFromNewSRVHeap(heap);
			});*/

		//m_ImGuiLayer->InitFromNewSRVHeap(m_ResourceManager->GetTextureDescriptorHeap());


		UpdateViewport();
	}

	void RenderFactory::UpdateViewport()
	{
		for (const auto& camera : m_CameraComps)
		{
			if (camera->IsActive())
			{
				camera->UpdateViewport();
			}
		}

		//for (const auto& viewport : m_Viewports)
		//{
		//	const auto& camera = viewport->GetCameraOwner().lock();

		//	if (viewport->IsChangeViewport())
		//	{
		//		const auto& directX = DirectX12::GetDirectX12();
		//		if (directX != nullptr)
		//		{
		//			directX->SetViewAndScissor(viewport->GetLeft(), viewport->GetTop(),
		//				viewport->GetWidth(), viewport->GetHeight());
		//		}

		//		viewport->UpdateViewportTexture(directX->GetDevice());

		//		if (camera != nullptr)
		//		{
		//			camera->ChangeProjectionInfo();
		//		}
		//		viewport->ChangedViewport();
		//	}

		//	if (camera != nullptr && camera->IsUpdateProjection())
		//	{
		//		camera->UpdateProjection(viewport->GetWidth(), viewport->GetHeight());
		//	}
		//}
	}

	const SPtr<class ImGuiLayer>& RenderFactory::CreateImGui()
	{
		m_ImGuiLayer = CreateSPtr<ImGuiLayer>(m_ResourceManager->GetDirectX12());

		m_ResourceManager->CreateSRVHeap([this](ID3D12DescriptorHeap* heap)
			{
				m_ImGuiLayer->InitFromNewSRVHeap(heap);
			});

		return m_ImGuiLayer;
	}

	void RenderFactory::Draw()
	{
		m_ResourceManager->Update();
		m_ShaderFactory->Update();

		m_ResourceManager->Draw();
		m_ShaderFactory->Draw();

		m_ImGuiLayer->Draw();
	}

	void RenderFactory::PrepareToNextDraw()
	{
		m_ResourceManager->PrepareToNextDraw();
		m_ShaderFactory->PrepareToNextDraw();
	}

	void RenderFactory::AddMeshCompForDraw(const SPtr<MeshComponent>& meshComp)
	{
		const auto& shader = m_ShaderFactory->GetShader(meshComp->GetMeshType());
		if (shader != nullptr)
			shader->AddMeshCompForDraw(meshComp);
	}

	void RenderFactory::RemoveMeshCompForDraw(const SPtr<MeshComponent>& meshComp)
	{
		const auto& shader = m_ShaderFactory->GetShader(meshComp->GetMeshType());
		if (shader != nullptr)
			shader->RemoveMeshCompForDraw(meshComp);
	}

	void RenderFactory::AddCameraComponent(const SPtr<CameraComponent>& camera)
	{
		m_CameraComps.push_back(camera);

		//아직 viewport는 1개이다. 따라서 main viewport에 플레이어 컨트롤러가 제어하는 camera가 담겨진다. <임시>
		//m_Viewports[0]->SetCamera(camera);
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

	SPtr<CameraComponent> RenderFactory::GetCameraComp(const std::string& ownerName)
	{
		auto iter = std::find_if(m_CameraComps.begin(), m_CameraComps.end(), [ownerName](const auto& camera)
			{
				return camera->GetOwner().lock()->GetActorName() == ownerName;
			});

		if (iter != m_CameraComps.end()) return *iter;
		else return nullptr;
	}

	RenderFactory* RenderFactory::s_Instance = nullptr;
}