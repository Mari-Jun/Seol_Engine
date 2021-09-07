#pragma once
#include "PARS/Math/Math.h"
#include "PARS/Component/Component.h"

namespace PARS
{
	enum class RenderState
	{
		Ready,
		Changed,
		Render,
		Invisible
	};

	enum class RenderType
	{
		HandMadeMesh,
		StaticMesh
	};

	struct CBWorldMat
	{
		Mat4 m_WorldMatrix;
		Mat4 m_WorldInverseTranspose;
	};

	class RenderComponent : public Component
	{
	public:
		RenderComponent(const std::string& name, RenderType type, int updateOrder = 200);
		virtual ~RenderComponent() = default;

		virtual void Initialize();
		virtual void Shutdown();
		virtual void Draw(ID3D12GraphicsCommandList* commandList) {}

		virtual void RenderReady(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) {}
		virtual void UpdateShaderVariables(std::map<std::string, BYTE*> variables);
		virtual void ReleaseUploadBuffers() {}

	public:
		void SetRenderState(RenderState state);
		RenderState GetRenderState() const { return m_RenderState; }
		RenderType GetRenderType() const { return m_Type; }

	protected:
		RenderState m_RenderState;
		RenderType m_Type;
	};
}