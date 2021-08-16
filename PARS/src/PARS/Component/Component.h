#pragma once
#include "PARS/Core/Core.h"
#include "PARS/Component/ComponentDetailFunction.h"

namespace PARS
{
	class Actor;

	class Component : public std::enable_shared_from_this<Component>
	{
	public:
		Component(const std::string& name = "Component", int updateOrder = 100);
		virtual ~Component() = default;
	
		void InitializeComponent();
		virtual void Initialize() {}
		virtual void InitializeDetailFunction();
		virtual void Shutdown() {}
		virtual void Update(float deltaTime) {}
		virtual void UpdateWorldMatrix() {}

	public:
		const WPtr<Actor>& GetOwner() const { return m_Owner; }
		void SetOwner(const WPtr<Actor>& owner) { m_Owner = owner; }
		const std::string& GetCompName() const { return m_CompName; }
		void SetCompName(const std::string& name) { m_CompName = name; }
		

	protected:
		WPtr<Actor> m_Owner;
		std::string m_CompName;
		int m_UpdateOrder;

	public:
		void AddDetailFunctionInfo(FunctionInfo&& info);
		void OnUpdateDetailInfo(std::function<void(const DetailInfo& info)> function);
		void SetDetailVisibleState(DVS state);
		void SetFunctionVisibleState(const std::string& treeName, FVS state);

	protected:
		UPtr<ComponentDetailFunction> m_CompDetailFunction;
	};
}


