#pragma once
#include "PARS/Component/ComponentDetailFunction.h"
#include "PARS/Component/Render/Mesh/MeshComponent.h"

namespace PARS
{
	class MeshCompDetailFunction : public ComponentDetailFunction
	{
	public:
		MeshCompDetailFunction() = default;

		virtual void CreateFunctionInfos() override;

	private:
		void MeshCountDetail(const SPtr<MeshComponent>& meshComp);

	};
}


