#pragma once
#include "PARS/Level/Level.h"
#include "PARS/GameState/GameState.h"

#undef near
#undef far

namespace PARS
{
	class DetailLayer;

	class DefaultLevel : public Level
	{
	public:
		DefaultLevel(const std::string& name);
		virtual ~DefaultLevel() = default;

		virtual void InitializeLevel() override;

	protected:
		UPtr<GameState> m_GameState = nullptr;

	public:
		void InGameCursor();
	};

	class Level2D : public DefaultLevel
	{
	public:
		Level2D(const std::string& name);
		virtual ~Level2D() = default;

		virtual void InitializeLevel() override;
	};

	class Level3D : public DefaultLevel
	{
	public:
		Level3D(const std::string& name);
		virtual ~Level3D() = default;

		virtual void InitializeLevel() override;
	};

}

