#pragma once
#include "PARS/Component/Render/Mesh/Mesh.h"
#include "PARS/Component/Render/RenderComponent.h"

namespace PARS
{
	class DirectX12;

	class MeshComponent : public RenderComponent
	{
	public:
		MeshComponent(const std::string& name = "Mesh Component");
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

		const SPtr<Mesh>& GetMesh() const { return m_Mesh; }

	protected:
		SPtr<Mesh> m_Mesh = nullptr;
	};

}


