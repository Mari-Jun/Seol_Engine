#pragma once
#include "PARS/Core/Core.h"

namespace PARS
{
	class DetailWindow
	{
	public:
		DetailWindow() = default;
		virtual ~DetailWindow() = default;

		virtual void Initialize() {}
		virtual void Shutdown() {}
		virtual void ProcessInput() {}
		virtual void Update() {}

	protected:
		std::string m_WindowName;

	public:
		void SetWindowName(const std::string& name) { m_WindowName = name; }
		const std::string& GetWindowName() const { return m_WindowName; }
	};
}



