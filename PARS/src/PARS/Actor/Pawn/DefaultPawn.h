#pragma once
#include "PARS/Actor/Pawn/Pawn.h"

namespace PARS
{
	class CameraComponent;

	class DefaultPawn : public Pawn
	{
	public:
		DefaultPawn(const std::string& name) : Pawn(name) {}
		virtual ~DefaultPawn() = default;

	protected:
		SPtr<CameraComponent> m_CameraComp;
	};


	class DefaultPawn2D : public DefaultPawn
	{
	public:
		DefaultPawn2D(const std::string& name = "Default Pawn 2D");
		virtual ~DefaultPawn2D();

		virtual void Initialize() override;
	};

	class DefaultPawn3D : public DefaultPawn
	{
	public:
		DefaultPawn3D(const std::string& name = "Default Pawn 3D");
		virtual ~DefaultPawn3D();

		virtual void Initialize() override;
	};
}
