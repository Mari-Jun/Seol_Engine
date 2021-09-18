#pragma once
#include "PARS/Layer/Layer.h"

namespace PARS
{
	class Actor;

	class ObjectLayer : public Layer
	{
	public:
		ObjectLayer(const std::string& name = "Object Layer");
		virtual ~ObjectLayer() = default;

		virtual void Update() override final;

	private:
		void UpdateObjects();

	public:
		void AddActorToLayer(const SPtr<Actor>& actor);
		void RemoveActorToLayer(const std::string& name);

	private:
		std::string m_SelectActorName;
		SPtr<Actor> m_SelectActor;
		std::multimap<std::string, const SPtr<Actor>> m_DetailActors;
	};
}


