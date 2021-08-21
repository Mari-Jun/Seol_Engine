#pragma once
#include "PARS/Component/Render/Mesh/MeshDetailFunction.h"
#include "PARS/Component/Render/Mesh/Handmade/HandmadeMeshComp.h"

namespace PARS
{
    class HandmadeMeshCompDetailFunction : public MeshCompDetailFunction
    {
	public:
		HandmadeMeshCompDetailFunction() = default;

		virtual void CreateFunctionInfos() override;

	private:
		void VertexInfoDetail(const SPtr<HandmadeMeshComponent>& meshComp);
    };
}


