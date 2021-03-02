#pragma once

namespace PARS
{
	struct ActionInfo
	{
		std::string actionName;
		int key;
		int secondKey;
	};

	struct KeyAxis
	{
		int key;
		float axis;
		int secondKey;
	};

	struct AxisActionInfo
	{
		std::string actionName;
		std::vector<KeyAxis> keyAxis;
	};

	enum class ActionType
	{
		Once,
		Loop,
		Axis,
		Release
	};

	class InputFactory
	{
	public:
		InputFactory();
		~InputFactory() = default;

		void ProcessInput();
		
		void AddOnceAction(std::string&& name, int key, const std::function<void()>& func, int secondKey = 0x00);
		void AddLoopAction(std::string&& name, int key, const std::function<void()>& func, int secondKey = 0x00);
		void AddAxisAction(std::string&& name, std::vector<KeyAxis>&& keyAndAxis, const std::function<void(float)>& func);
		void AddReleaseAction(std::string&& name, int key, const std::function<void()>& func, int secondKey = 0x00);

		void ActiceAction(ActionType type, std::string&& name, bool active);

	private:
		std::vector<ActionInfo> m_OnceActionsInfo;
		std::unordered_map<std::string, std::pair<bool, std::function<void()>>> f_OnceActions;
		std::vector<ActionInfo> m_LoopActionsInfo;
		std::unordered_map<std::string, std::pair<bool, std::function<void()>>> f_LoopActions;
		std::vector<AxisActionInfo> m_AxisActionsInfo;
		std::unordered_map<std::string, std::pair<bool, std::function<void(float)>>> f_AxisActions;
		std::vector<ActionInfo> m_ReleaseActionsInfo;
		std::unordered_map<std::string, std::pair<bool, std::function<void()>>> f_ReleaseActions;
	};
}


