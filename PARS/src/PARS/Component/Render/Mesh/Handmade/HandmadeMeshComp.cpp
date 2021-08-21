#include "stdafx.h"
#include "PARS/Component/Render/Mesh/Handmade/HandmadeMeshComp.h"
#include "PARS/Component/Render/Mesh/Handmade/HandmadeMeshDF.h"

namespace PARS
{
	HandmadeMeshComponent::HandmadeMeshComponent()
		: MeshComponent("Handmade Mesh Component")
	{
	}

	void HandmadeMeshComponent::InitializeDetailFunction()
	{
		m_CompDetailFunction = CreateUPtr<HandmadeMeshCompDetailFunction>();
	}
}