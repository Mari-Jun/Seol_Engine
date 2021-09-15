#pragma once
#include "PARS/Component/Render/Mesh/MeshComponent.h"
#include "PARS/Util/Content/AssetStore.h"

namespace PARS
{
	class StaticMeshComponent final : public MeshComponent
	{
	public:
		StaticMeshComponent();
		virtual ~StaticMeshComponent() = default;

		virtual void InitializeDetailFunction() override;
		virtual void UpdateShaderVariables(std::map<std::string, BYTE*> variables) override;

	public:
		bool SetMesh(std::string&& path);
		virtual void SetMesh(const SPtr<Mesh>& mesh) override;
	};
}


