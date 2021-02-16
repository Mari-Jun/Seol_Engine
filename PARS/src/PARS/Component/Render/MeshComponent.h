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

	public:
		enum class FileType
		{
			HandMade,
			Obj
		};

		template<typename T, typename ... Args>
		constexpr void SetMesh(FileType type, std::string&& fileName, Args&& ... args)
		{
			//fileName은 현재 미사용 나중에 Cache기능 생성시 사용

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
		}
		const SPtr<Mesh>& GetMesh() const { return m_Mesh; }


	private:
		SPtr<Mesh> m_Mesh;
	};

}


