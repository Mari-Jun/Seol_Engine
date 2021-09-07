#include "stdafx.h"
#include "PARS/Component/Component.h"
#include "PARS/Actor/Actor.h"

namespace PARS
{
	Component::Component(const std::string& name, int updateOrder)
		: m_CompName(name)
		, m_UpdateOrder(updateOrder)
	{
	}

	Component::~Component()
	{
		PARS_INFO(GetCompName() + " is dead");
	}

	void Component::InitializeComponent()
	{
		Initialize();
		InitializeDetailFunction();
		if (m_CompDetailFunction != nullptr)
		{
			m_CompDetailFunction->Initialize(weak_from_this());
		}
	}

	void Component::InitializeDetailFunction()
	{
		m_CompDetailFunction = CreateUPtr<ComponentDetailFunction>();
		SetDetailVisibleState(DVS::HideAll);
	}

	void Component::ShutdownComponent()
	{
		m_CompDetailFunction->Shutdown();
		Shutdown();
	}

	void Component::AddDetailFunctionInfo(FunctionInfo&& info)
	{
		m_CompDetailFunction->AddFunctionInfo(std::move(info));
	}

	void Component::OnUpdateDetailInfo(std::function<void(const DetailInfo& info)> function)
	{
		function(m_CompDetailFunction->GetDetailInfo());
	}

	void Component::SetDetailVisibleState(DVS state)
	{
		m_CompDetailFunction->SetDetailVisibleState(state);
	}

	void Component::SetFunctionVisibleState(const std::string& treeName, FVS state)
	{
		m_CompDetailFunction->SetFunctionVisibleState(treeName, state);
	}
}
