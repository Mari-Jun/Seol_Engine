#pragma once
#include "PARS/Component/Render/Mesh.h"
#include "PARS/Component/Render/RenderComponent.h"

namespace PARS
{
	class DirectX12;

	class MeshComponent : public RenderComponent
	{
	public:
		MeshComponent();
		virtual ~MeshComponent() = default;

		virtual void Initialize() override;
		virtual void Shutdown() override;
		virtual void Draw(ID3D12GraphicsCommandList* commandList) override;

		virtual void RenderReady(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) override;
		virtual void ReleaseUploadBuffers();

	public:
		enum class FileType
		{
			HandMade,
			Obj
		};

		template<typename T, typename ... Args>
		constexpr void SetMesh(FileType type, std::string&& fileName, Args&& ... args)
		{
			//Mesh 교체 여부 확인
			if (m_Mesh != nullptr)
			{
				m_Mesh->Shutdown();
				m_Mesh = nullptr;
				ChangeComponentItem();
			}

			//이미 Load된적이 있는지 Cache데이터에서 찾는다. 
			const auto& factory = RenderComponentFactory::GetRenderComponentFactory();
			m_Mesh = factory->GetMesh(std::move(fileName));

			if (m_Mesh == nullptr)
			{
				switch (type)
				{
				case PARS::MeshComponent::FileType::HandMade:
					m_Mesh = CreateSPtr<T>();
					std::reinterpret_pointer_cast<T>(m_Mesh)->SetVertex(std::forward<Args>(args)...);
					break;
				case PARS::MeshComponent::FileType::Obj:
					//아직 미구현
					break;
				}

				//(HandMade는 Cache에 저장하지 않는다.)
				if (type != FileType::HandMade)
				{
					factory->SaveMesh(std::move(fileName), m_Mesh);
				}
			}		
		}

		const SPtr<Mesh>& GetMesh() const { return m_Mesh; }

	private:
		SPtr<Mesh> m_Mesh = nullptr;
	};

}


