#include "stdafx.h"
#include "PARS/Actor/Pawn/DefaultPawn.h"
#include "PARS/Component/Camera/Ortho/OrthoCameraComp.h"
#include "PARS/Component/Camera/Perspective/PerspectiveCameraComp.h"

namespace PARS
{
	DefaultPawn2D::DefaultPawn2D(const std::string& name)
		: DefaultPawn(name)
	{
	}

	DefaultPawn2D::~DefaultPawn2D()
	{
	}

	void DefaultPawn2D::Initialize()
	{
		DefaultPawn::Initialize();
		m_CameraComp = CreateSPtr<OrthoCameraComponent>();
		AddComponent(m_CameraComp);
	}

	DefaultPawn3D::DefaultPawn3D(const std::string& name)
		: DefaultPawn(name)
	{
	}

	DefaultPawn3D::~DefaultPawn3D()
	{
	}

	void DefaultPawn3D::Initialize()
	{
		DefaultPawn::Initialize();
		m_CameraComp = CreateSPtr<PerspectiveCameraComponent>();
		AddComponent(m_CameraComp);
	}
	
}
