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

	void RenderComponentFactory::Draw(ShaderType type)
	{
		for (const auto& component : m_RenderComponents[type])
		{
			component->Draw(m_DirectX12->GetCommandList());
		}
	}

	void RenderComponentFactory::AddRenderComponent(ShaderType type, const SPtr<RenderComponent>& component)
	{
		//임시로 넣을때마다 초기화하고 명령대기열에 추가하자.
		auto commandQueue = m_DirectX12->GetCommandQueue();
		auto commandList = m_DirectX12->GetCommandList();
		auto commandAllocator = m_DirectX12->GetCommandAllocator();

		commandList->Reset(commandAllocator, nullptr);

		
		auto iter = m_RenderComponents.insert({ type, {component} });
		if (!iter.second)
		{
			iter.first->second.emplace_back(component);
			component->RenderReady(m_DirectX12->GetDevice(), m_DirectX12->GetCommandList());
		}

		commandList->Close();
		ID3D12CommandList* commandLists[] = { commandList };
		commandQueue->ExecuteCommandLists(_countof(commandLists), commandLists);

		m_DirectX12->WaitForGpuCompelete();
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
