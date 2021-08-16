#include "stdafx.h"
#include "PARS/Layer/EngineLayer/DetailLayer/DetailFunction.h"

namespace PARS
{
	void DetailFunction::Initailize(const std::string& name)
	{
		m_DetailInfo.headerName = name;
	}

	void DetailFunction::AddFunctionInfo(FunctionInfo&& info)
	{
		m_DetailInfo.functionInfos.emplace_back(std::move(info));
	}

	void DetailFunction::SetDetailVisibleState(DVS state)
	{
		m_DetailInfo.state = state;
	}

	void DetailFunction::SetFunctionVisibleState(const std::string& treeName, FVS state)
	{
		auto function = std::find_if(m_DetailInfo.functionInfos.begin(), m_DetailInfo.functionInfos.end(),
			[treeName](const FunctionInfo& function)
			{ return function.treeName == treeName; });

		if (function != m_DetailInfo.functionInfos.end())
		{
			function->state = state;
		}
	}
}