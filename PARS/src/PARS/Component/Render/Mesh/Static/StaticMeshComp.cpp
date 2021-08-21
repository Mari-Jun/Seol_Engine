#include "stdafx.h"
#include "PARS/Component/Render/Mesh/Static/StaticMeshComp.h"
#include "PARS/Component/Render/Mesh/Static/StaticMeshDF.h"

namespace PARS
{
	StaticMeshComponent::StaticMeshComponent()
		: MeshComponent("Static Mesh Component")
	{
	}

	void StaticMeshComponent::InitializeDetailFunction()
	{
		m_CompDetailFunction = CreateUPtr<StaticMeshCompDetailFunction>();
	}
}
