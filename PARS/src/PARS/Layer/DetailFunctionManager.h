#pragma once

namespace PARS
{
	struct DetailFunction
	{
		std::string treeName;
		std::function<void()> function;
	};

	class DetailFunctionManager
	{
	public:
		DetailFunctionManager() = default;

		void AddDetailFunction(const std::string& treeName, const std::function<void()>& func) { m_DetailFunctions.emplace_back(DetailFunction{ treeName, func }); }
		const std::vector<DetailFunction>& GetDetailFunctions() const { return m_DetailFunctions; }

	private:
		std::vector<DetailFunction> m_DetailFunctions;
	};
}

