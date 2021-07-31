#include "stdafx.h"
#include "PARS/Layer/EngineLayer/DetailLayer/DetailFunctionFactory.h"

namespace PARS
{
	void DetailFunctionFactory::AddFunctionInfo(const FunctionInfo& info)
	{
		m_FunctionInfos.push_back(info);
	}

	void DetailFunctionFactory::AddFunctionInfo(FunctionInfo&& info)
	{
		m_FunctionInfos.emplace_back(std::move(info));
	}
}