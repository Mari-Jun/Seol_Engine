#pragma once

namespace PARS
{
	class D3DUtil
	{
	public:
		static ID3D12Resource* CreateBufferResource(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const void* initData, UINT byteSize,
			D3D12_HEAP_TYPE heapType = D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATES resourceState = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, ID3D12Resource** uploadBuffer = nullptr);
	};
}

