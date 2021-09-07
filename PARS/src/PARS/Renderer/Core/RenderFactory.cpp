#include "stdafx.h"
#include "PARS/Renderer/Core/RenderFactory.h"
#include "PARS/Core/Window.h"

namespace PARS
{
	RenderFactory::RenderFactory(const SPtr<DirectX12>& directX)
	{
		m_ShaderFactory = CreateUPtr<ShaderFactory>(directX);
	}

	bool RenderFactory::Initialize()
	{
		s_Instance = this;

		m_Viewports.emplace_back(CreateSPtr<Viewport>());

		m_ShaderFactory->Initialize();
		return true;
	}

	void RenderFactory::Shutdown()
	{
		m_ShaderFactory->Shutdown();
	}

	void RenderFactory::Update()
	{
		UpdateViewport();

		m_ShaderFactory->Update();		
	}

	void RenderFactory::UpdateViewport()
	{
		for (const auto& viewport : m_Viewports)
		{
			const auto& camera = viewport->GetCameraOwner().lock();

			if (viewport->IsChangeViewport())
			{
				const auto& directX = DirectX12::GetDirectX12();
				if (directX != nullptr)
				{
					directX->SetViewAndScissor(viewport->GetLeft(), viewport->GetTop(),
						viewport->GetWidth(), viewport->GetHeight());
				}

				if (camera != nullptr)
				{
					camera->ChangeProjectionInfo();
				}
				viewport->ChangedViewport();
			}

			if (camera != nullptr && camera->IsUpdateProjection())
			{
				camera->UpdateProjection(viewport->GetWidth(), viewport->GetHeight());
			}
		}
	}

	void RenderFactory::Draw()
	{
		m_ShaderFactory->Draw();
	}

	void RenderFactory::PrepareToNextDraw()
	{
		m_ShaderFactory->PrepareToNextDraw();
	}


	void RenderFactory::AddRenderComponent(RenderType type, const SPtr<RenderComponent>& component)
	{
		AddPrepareComponent(type, component);
		const auto& shader = m_ShaderFactory->GetShader(type);
		if (shader != nullptr)
			shader->AddRenderComponent(component);
	}

	void RenderFactory::AddPrepareComponent(RenderType type, const SPtr<class RenderComponent>& component)
	{
		RenderState state = component->GetRenderState();
		if (state == RenderState::Ready || state == RenderState::Changed)
		{
			const auto& shader = m_ShaderFactory->GetShader(type);
			if (shader != nullptr)
				shader->AddPrepareComponent(component);
		}
	}

	void RenderFactory::RemoveRenderComponent(RenderType type, const SPtr<RenderComponent>& component)
	{
		const auto& shader = m_ShaderFactory->GetShader(type);
		if (shader != nullptr)
			shader->RemoveRenderComponent(component);
	}


	void RenderFactory::AddCameraComponent(const SPtr<CameraComponent>& camera)
	{
		m_CameraComps.push_back(camera);

		//아직 viewport는 1개이다. 따라서 main viewport에 플레이어 컨트롤러가 제어하는 camera가 담겨진다. <임시>
		m_Viewports[0]->SetCamera(camera);
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

	RenderFactory* RenderFactory::s_Instance = nullptr;
}