#pragma once

namespace PARS
{
	struct FunctionInfo
	{
		std::string treeName;
		std::function<void()> function;
	};

	class DetailFunctionFactory
	{
	public:
		DetailFunctionFactory() = default;

		void AddFunctionInfo(const FunctionInfo& info);
		void AddFunctionInfo(FunctionInfo&& info);

		const std::vector<FunctionInfo>& GetFunctionInfos() const { return m_FunctionInfos; }

	private:
		std::vector<FunctionInfo> m_FunctionInfos;
	};
}


