#pragma once

#include <PARS.h>

namespace PARS
{
	using FList = std::vector<std::function<void()>>;

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		void Initialize() override;
		void Update() override;

	private:
		void ShowLevel0();

		void ShowLevelHeader(const char* levelName, FList& physics, FList& rendering);
		void ShowListNode(const char* nodeName, FList& functions);
		void ShowSimulationNode(SPtr<Level>&& newLevel, const char* explaination);
	};
}