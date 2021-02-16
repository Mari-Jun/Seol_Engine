#include "stdafx.h"
#include "PARS/Renderer/DirectX12/DirectX12.h"
#include "PARS/Component/Render/RenderComponent.h"
#include "PARS/Renderer/Core/RenderComponentFactory.h"

namespace PARS
{
	RenderComponentFactory::RenderComponentFactory(const SPtr<DirectX12>& directX)
		: m_DirectX12(directX)
	{
	}

	bool RenderComponentFactory::Initialize()
	{
		s_Instance = this;
		return true;
	}

	void RenderComponentFactory::Shutdown()
	{
	}

	void RenderComponentFactory::PrepareDraw()
	{
		if (!m_PrepareComponents.empty())
		{
			auto commandQueue = m_DirectX12->GetCommandQueue();
			auto commandList = m_DirectX12->GetCommandList();
			auto commandAllocator = m_DirectX12->GetCommandAllocator();

			commandList->Reset(commandAllocator, nullptr);

			for (auto& comps : m_PrepareComponents)
			{
				auto iter = m_RenderComponents.emplace(std::move(comps));
				if (!iter.second)
				{
					for (auto& comp : comps.second)
					{
						comp->RenderReady(m_DirectX12->GetDevice(), m_DirectX12->GetCommandList());
						iter.first->second.emplace_back(std::move(comp));
					}
				}
			}

			commandList->Close();
			ID3D12CommandList* commandLists[] = { commandList };
			commandQueue->ExecuteCommandLists(_countof(commandLists), commandLists);

			m_DirectX12->WaitForGpuCompelete();

			m_PrepareComponents.clear();
		}
	}

	void RenderComponentFactory::Draw(ShaderType type)
	{
		for (const auto& component : m_RenderComponents[type])
		{
			component->Draw(m_DirectX12->GetCommandList());
		}
	}

	void RenderComponentFactory::AddRenderComponent(ShaderType type, const SPtr<RenderComponent>& component)
	{
		auto iter = m_PrepareComponents.emplace(type, std::vector<SPtr<RenderComponent>>{component});
		if (!iter.second)
		{
			iter.first->second.emplace_back(component);
			component->RenderReady(m_DirectX12->GetDevice(), m_DirectX12->GetCommandList());
		}		
	}

	void RenderComponentFactory::RemoveRenderComponent(ShaderType type, const SPtr<RenderComponent>& component)
	{
		auto rComp = m_RenderComponents.find(type);
		if (rComp != m_RenderComponents.end())
		{
			auto iter = std::find_if(rComp->second.begin(), rComp->second.end(),
				[&component](const SPtr<RenderComponent>& comp)
				{return component == comp; });
			if (iter != rComp->second.end())
			{
				rComp->second.erase(iter);
				if (rComp->second.empty())
				{
					m_RenderComponents.erase(type);
				}
			}
		}
	}

	SPtr<class Mesh> RenderComponentFactory::GetMesh(std::string&& fileName)
	{
		return SPtr<class Mesh>();
	}

	RenderComponentFactory* RenderComponentFactory::s_Instance = nullptr;
}
