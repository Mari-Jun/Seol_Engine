#include "stdafx.h"
#include "PARS/Component/Component.h"
#include "PARS/Component/ComponentDetailFunction.h"

namespace PARS
{
    void ComponentDetailFunction::Initialize(const WPtr<Component>& comp)
    {
        m_Component = comp;
        if (m_Component.lock()->IsUseDefualtDetail())
        {
            AddFunctionInfo();
        }
    }
}
