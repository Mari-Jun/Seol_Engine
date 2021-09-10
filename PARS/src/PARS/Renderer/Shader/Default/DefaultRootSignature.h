#pragma once
#include "PARS/Renderer/Shader/Core/RootSignature.h"
#include "PARS/Component/Light/LightComponent.h"

namespace PARS
{
	struct CBDefaultPass : public CBPass
	{
		Mat4 m_ViewProj = Mat4::Identity;
		Vec3 m_EyePos = Vec3::Zero;
		float m_Padding1 = 0.0f;
		LightCount m_LightCount;
		float m_Padding2 = 0.0f;
		Vec4 m_AmbientLight = Vec4::Zero;
		LightCB m_Lights[16];
	};

	class DefaultRootSignature : public RootSignature
	{
	public:
		DefaultRootSignature(const SPtr<DirectX12>& directX);
		virtual ~DefaultRootSignature() = default;

		virtual void Shutdown() override;

	private:
		virtual void CreateRootSignature(ID3D12Device* device) override;
		virtual void CreateShaders() override;
		virtual void RenderReady(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) override;
		virtual void UpdateShaderVariables() override;
		virtual void DrawPassFrame(ID3D12GraphicsCommandList* commandList) override;

	private:
		ID3D12Resource* m_DefaultPassCB = nullptr;
		CBDefaultPass* m_DefaultPassMappedData = nullptr;

		ID3D12Resource* m_MaterialCB = nullptr;
		BYTE* m_MaterialMappedData = nullptr;
	};
}


