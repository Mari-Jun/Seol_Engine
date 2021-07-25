#pragma once

#include "imgui.h"

namespace PARS
{
	struct FunctionInfo
	{
		std::string treeName;
		std::function<void()> function;
	};

	class DetailFunction
	{
	public:
		DetailFunction() = default;

		//void AddDetailFunction(const std::string& treeName, const std::function<void()>& func) { m_FunctionInfos.emplace_back(FunctionInfo{ treeName, func }); }
		const std::vector<FunctionInfo>& GetFunctionInfos() const { return m_FunctionInfos; }

	protected:
		std::vector<FunctionInfo> m_FunctionInfos;

		ImVec4 m_TextColor = { 0.0f, 1.0f, 1.0f, 1.0f };
	};

}

