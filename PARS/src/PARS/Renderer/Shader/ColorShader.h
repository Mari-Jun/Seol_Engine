#pragma once
#include "PARS/Renderer/Shader/Core/Shader.h"
#include "PARS/Component/Light/LightComponent.h"

namespace PARS
{
	struct CBWorldMat
	{
		Mat4 m_WorldMatrix;
		Mat4 m_WorldInverseTranspose;
	};

	/*struct CBMaterial
	{
		Vec4 m_DiffuseAlbedo = { 1.0f, 1.0f, 1.0f, 1.0f };
		Vec3 m_FresnelR0 = { 0.01f, 0.01f, 0.0f };
		float m_Roughness = 0.25f;
	};*/

	struct CBColorPass : public CBPass
	{
		Mat4 m_ViewProj = Mat4::Identity;
		Vec3 m_EyePos = Vec3::Zero;
		float m_Padding1 = 0.0f;
		LightCount m_LightCount;
		float m_Padding2 = 0.0f;
		Vec4 m_AmbientLight = Vec4::Zero;
		LightCB m_Lights[16];
	};

	class ColorShader : public Shader
	{
	public:
		ColorShader(const SPtr<DirectX12>& directX);
		virtual ~ColorShader() = default;

		virtual void Shutdown() override;

	private:
		virtual void Update(ID3D12GraphicsCommandList* commandList) override;
		virtual void RenderReady(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, UINT numOfObject) override;
		void UpdateShaderVariables(ID3D12GraphicsCommandList* commandList, const CBColorPass& cbPass);
		virtual void DrawRenderComp(ID3D12GraphicsCommandList* commandList, int index) override;
		virtual void DrawPassFrame(ID3D12GraphicsCommandList* commandList);
		 
	public:
		virtual void CreateShader() override;
		virtual void CreateInputLayout()  override;
		virtual bool CreatePSO(ID3D12RootSignature* rootSignature) override;

	protected:
		ID3D12Resource* m_WorldMatCB = nullptr;
		BYTE* m_WorldMatMappedData = nullptr;
		
		ID3D12Resource* m_ColorPassCB = nullptr;
		BYTE* m_ColorPassMappedData = nullptr;
	};

}

