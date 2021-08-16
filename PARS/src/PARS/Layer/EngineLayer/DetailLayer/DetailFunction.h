#pragma once
#include "PARS/Core/Core.h"

namespace PARS
{
	enum class DetailVisibleState
	{
		Activate,
		Disabled,
		HideDefault,
		Hide,
		HideAll,
	};

	enum class FunctionVisibleState
	{
		Activate,
		Disabled,
		Hide
	};

	using DVS = DetailVisibleState;
	using FVS = FunctionVisibleState;

	struct FunctionInfo
	{
		std::string treeName;
		std::function<void()> function;
		bool isDefualt = true;
		FVS state = FVS::Activate;
	};

	struct DetailInfo
	{
		std::string headerName;
		std::vector<FunctionInfo> functionInfos;
		DVS state = DVS::Activate;
	};


	class DetailFunction
	{
	public:
		DetailFunction() = default;

		void Initailize(const std::string& name);
		void AddFunctionInfo(FunctionInfo&& info);

		void SetDetailVisibleState(DVS state);
		void SetFunctionVisibleState(const std::string& treeName, FVS state);

		const DetailInfo& GetDetailInfo() const { return m_DetailInfo; }

	private:
		DetailInfo m_DetailInfo;
	};
}


