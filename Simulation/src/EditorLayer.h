#pragma once

#include <PARS.h>

namespace PARS
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		void Initialize() override;
		void Update() override;
	};
}