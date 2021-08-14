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

	void Component::InitializeComponent()
	{
		Initialize();
		InitializeDetailFunction();
		if (m_CompDetailFunction != nullptr)
		{
			m_CompDetailFunction->Initialize(weak_from_this());
		}
	}

	void Component::AddDetailFunctionInfo(FunctionInfo&& info)
	{
		m_Owner.lock()->AddDetailFunctionInfo(std::move(info));
	}
}
