#include "stdafx.h"
#include "PARS/Component/ComponentDetailFunction.h"

namespace PARS
{
    void ComponentDetailFunction::Initialize(const WPtr<Actor>& owner, const WPtr<Component>& comp)
    {
        m_Component = comp;
        DetailFunction::Initialize(owner);
    }
}
