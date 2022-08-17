#pragma once

#include "PARS/Util/Content/Asset.h"
#include "PARS/Input/InputFactory.h"
#include "PARS/Layer/EngineLayer/DetailLayer/DetailFunction.h"

namespace PARS
{
	class ActorManager;

	enum class LevelState
	{
		InGame, Editor, Paused, Dead
	};

	class Level : public Asset
	{
	public:
		Level(const std::string& name = "Defualt_Level");
		virtual ~Level();

		virtual void InitializeLevel() {}
		virtual	void ShutdownLevel() {}
		void Initialize();		
		void Shutdown();
		void ProcessInput();
		virtual void LevelInput() {}
		virtual void Update(float deltaTime);
		void UpdateActorManager(float deltaTime);
		virtual void UpdateLevel(float deltaTime) {};

		virtual void AddActor(const SPtr<class Actor>& actor);
		virtual void RemoveActor(const SPtr<class Actor>& actor);

	public:
		//For file
		void SaveLevel(std::ofstream& file);
		void LoadLevel(std::ifstream& file);

	protected:
		std::string m_LevelName;
		LevelState m_LevelState;

	private:
		UPtr<ActorManager> m_ActorManager;
		UPtr<InputFactory> m_EditorInputFactory;
		UPtr<InputFactory> m_InGameInputFactory;

	public:
		const std::string& GetLevelName() const { return m_LevelName; }
		LevelState GetLevelState() const { return m_LevelState; }
		void SetLevelState(LevelState state) { m_LevelState = state; }

	protected:
		void AddOnceAction(std::string&& name, int key, const std::function<void()>& func, bool isEditor = false);
		void AddLoopAction(std::string&& name, int key, const std::function<void()>& func, bool isEditor = false);
		void AddAxisAction(std::string&& name, std::vector<KeyAxis>&& keyAndAxis, const std::function<void(float)>& func, bool isEditor = false);
		void AddReleaseAction(std::string&& name, int key, const std::function<void()>& func, bool isEditor = false);
		void ActiveAction(ActionType type, std::string&& name, bool active, bool isEditor = false);

	public:
		void AddLayer(const SPtr<class Layer>& layer);
		void AddLevelSettingFunctionInfo(FunctionInfo&& info);
		void OnUpdateDetailInfo(std::function<void(const DetailInfo& info)> function);

	private:
		std::vector<WPtr<class Layer>> m_Layers;
		UPtr<DetailFunction> m_DetailFunction;

	public:
		void SetLayerActive();
		void SetLayerHide();
		void Destroy() { m_LevelState = LevelState::Dead; }
	};
}


