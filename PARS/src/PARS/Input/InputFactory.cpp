#include "stdafx.h"
#include "PARS/Input/InputFactory.h"
#include "PARS/Input/Input.h"

namespace PARS
{
	InputFactory::InputFactory()
	{
	}

	void InputFactory::ProcessInput()
	{
		for (const auto& action : m_OnceActionsInfo)
		{
			if (Input::IsKeyFirstPressed(action.key) && f_OnceActions[action.actionName].first)
			{
				f_OnceActions[action.actionName].second();
			}
		}

		for (const auto& action : m_LoopActionsInfo)
		{
			if (Input::IsKeyPressed(action.key) && f_LoopActions[action.actionName].first)
			{
				f_LoopActions[action.actionName].second();
			}
		}

		for (const auto& action : m_AxisActionsInfo)
		{
			if (f_AxisActions[action.actionName].first)
			{
				float axis = 0.0f;
				for (const auto& ka : action.keyAxis)
				{
					if (Input::IsKeyPressed(ka.key))
					{
						axis += ka.axis;
					}
				}

				f_AxisActions[action.actionName].second(axis);
			}
		}
	}

	void InputFactory::AddOnceAction(std::string&& name, int key, const std::function<void()>& func)
	{
		m_OnceActionsInfo.emplace_back(ActionInfo{ name, key });
		f_OnceActions.emplace(name, std::pair{ true, func });
	}

	void InputFactory::AddLoopAction(std::string&& name, int key, const std::function<void()>& func)
	{
		m_LoopActionsInfo.emplace_back(ActionInfo{ name, key });
		f_LoopActions.emplace(name, std::pair{ true, func });
	}

	void InputFactory::AddAxisAction(std::string&& name, std::vector<KeyAxis>&& keyAndAxis, const std::function<void(float)>& func)
	{
		m_AxisActionsInfo.emplace_back(AxisActionInfo{ name, keyAndAxis });
		f_AxisActions.emplace(name, std::pair{ true, func });
	}

	void InputFactory::ActiceAction(ActionType type, std::string&& name, bool active)
	{
		switch (type)
		{
		case PARS::ActionType::Once: f_OnceActions[name].first = active; break;
		case PARS::ActionType::Loop: f_LoopActions[name].first = active; break;
		case PARS::ActionType::Axis: f_AxisActions[name].first = active; break;
		}
	}
}
