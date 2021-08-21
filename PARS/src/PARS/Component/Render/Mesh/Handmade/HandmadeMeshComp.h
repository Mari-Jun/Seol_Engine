#pragma once
#include "PARS/Component/Render/Mesh/MeshComponent.h"

namespace PARS
{
    class HandmadeMeshComponent final : public MeshComponent
    {
    public:
        HandmadeMeshComponent();
        virtual ~HandmadeMeshComponent() = default;

        virtual void InitializeDetailFunction() override;

		template<typename T, typename ... Args>
		constexpr void SetMesh(Args&& ... args)
		{
			if (m_Mesh != nullptr)
			{
				m_Mesh->Shutdown();
				SetRenderState(RenderState::Ready);
			}
			else
			{
				m_Mesh = CreateSPtr<T>();
			}

			std::reinterpret_pointer_cast<T>(m_Mesh)->SetVertex(std::forward<Args>(args)...);
		}
    };
}


