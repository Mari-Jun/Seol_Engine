#include "stdafx.h"
#include "PARS/Component/Component.h"

namespace PARS
{
	Component::Component(const std::string& name, int updateOrder)
		: m_CompName(name)
		, m_UpdateOrder(updateOrder)
	{
		std::cout << GetCompName() << "의 등장" << std::endl;
	}

	Component::~Component()
	{
		std::cout << GetCompName() << "의 사망" << std::endl;
	}

	void Component::InitializeComponent()
	{
		Initialize();
		InitializeDetailFunction();
		if (m_CompDetailFunction != nullptr)
		{
			m_CompDetailFunction->Initialize(m_Owner, weak_from_this());
		}
	}
}
