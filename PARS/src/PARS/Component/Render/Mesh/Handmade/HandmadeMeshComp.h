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
		virtual void Shutdown() override;

		virtual void RenderReady(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) override;

		template<typename ... Args>
		constexpr void SetMesh(Args&& ... args)
		{
			if (m_Mesh != nullptr)
			{
				m_Mesh->Shutdown();
				m_Mesh = nullptr;
			}
			else
			{
				m_Mesh = CreateSPtr<DiffuseMesh>();
			}

			std::reinterpret_pointer_cast<DiffuseMesh>(m_Mesh)->SetVertex(std::forward<Args>(args)...);
		}
    };
}


