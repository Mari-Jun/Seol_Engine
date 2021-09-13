#pragma once
#include "PARS/Component/Render/Mesh/MeshDetailFunction.h"
#include "PARS/Component/Render/Mesh/Static/StaticMeshComp.h"

namespace PARS
{
	class StaticMeshCompDetailFunction : public MeshCompDetailFunction
	{
	public:
		StaticMeshCompDetailFunction() = default;

		virtual void CreateFunctionInfos() override;

	private:
		void SetMeshDetail(const SPtr<StaticMeshComponent>& meshComp);
		void SetMaterialDetail(const SPtr<StaticMeshComponent>& meshComp);
	};
}


