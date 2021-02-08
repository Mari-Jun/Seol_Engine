#pragma once

#include <PARS.h>

namespace PARS
{
	class ClearColorLayer : public Layer
	{
	public:
		ClearColorLayer();
		virtual ~ClearColorLayer();

		void Update() override;
		void Shutdown() override;

		void OnDestroy(std::function<void()> func) { f_Destroy = func; }

	private:
		std::function<void()> f_Destroy;
	};
}



