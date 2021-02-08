#pragma once

#include <PARS.h>
#include "EditorLayer.h"

namespace PARS
{
	class EditorLevel : public Level
	{
	public:
		EditorLevel()
			: Level("Editor Level")
		{

		}

		virtual ~EditorLevel() = default;

		void InitializeLevel() override
		{
			AddLayer(PARS::CreateSPtr<PARS::EditorLayer>());
		}
	};
}