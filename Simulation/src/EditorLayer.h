#pragma once

#include <PARS.h>

namespace PARS
{
	using FList = std::vector<std::function<void()>>;
	using FLevelList = std::vector<std::function<void(int level)>>;

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		void Initialize() override;
		void Update() override;

	private:
		void SelectLevel(int level);
		void SetLevel0();
		void SetLevel1();
		void SetLevel2();
		void SetLevel3();
		void SetLevel4();
		void SetLevel5();
		void SetLevel6();
		void SetLevel7();
		void SetLevel8();
		void SetLevel9();
		void SetLevel10();

		void ShowLevelHeader(int level, FList& physics, FList& rendering);
		void ShowListNode(const char* nodeName, FList& functions);
		void ShowSimulationNode(SPtr<Level>&& newLevel, const char* explaination);

	private:
		FLevelList m_BasicFuntions;
		std::array<FList, 11> m_PhysicsFunctions;
		std::array<FList, 11> m_RenderingFunctions;

	};
}