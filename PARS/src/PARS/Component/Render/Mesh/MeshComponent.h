#pragma once
#include "PARS/Component/Render/Mesh/Mesh.h"
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
		virtual void InitializeDetailFunction() override;
		virtual void Shutdown() override;
		virtual void Draw(ID3D12GraphicsCommandList* commandList) override;

		virtual void RenderReady(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) override;
		virtual void ReleaseUploadBuffers() override;

	public:
		enum class FileType
		{
			Obj
		};

		template<typename T, typename ... Args>
		constexpr bool SetMesh(FileType type, std::string&& fileName, Args&& ... args)
		{
			//Mesh 교체 여부 확인
			if (m_Mesh != nullptr)
			{
				m_Mesh = nullptr;
				ChangeComponentItem();
			}

			//이미 Load된적이 있는지 Cache데이터에서 찾는다. 
			const auto& factory = RenderComponentFactory::GetRenderComponentFactory();
			m_Mesh = factory->GetMesh(fileName);
		
			if (m_Mesh == nullptr)
			{
				m_Mesh = CreateSPtr<T>();
				switch (type)
				{
				case PARS::MeshComponent::FileType::Obj:
					if (!std::reinterpret_pointer_cast<T>(m_Mesh)->LoadObj(fileName))
					{
						std::reinterpret_pointer_cast<T>(m_Mesh)->LoadObj("Default/Box");
						return false;
					}
					break;
				}

				factory->SaveMesh(fileName, m_Mesh);
				return true;
			}		

			return true;
		}

		template<typename T, typename ... Args>
		constexpr void SetHandMadeMesh(Args&& ... args)
		{
			if (m_Mesh != nullptr)
			{
				m_Mesh->Shutdown();
				ChangeComponentItem();
			}
			else
			{
				m_Mesh = CreateSPtr<T>();
			}
			
			std::reinterpret_pointer_cast<T>(m_Mesh)->SetVertex(std::forward<Args>(args)...);
		}

		const SPtr<Mesh>& GetMesh() const { return m_Mesh; }

	private:
		SPtr<Mesh> m_Mesh = nullptr;
	};

}


