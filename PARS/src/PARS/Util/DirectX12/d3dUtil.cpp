#include "stdafx.h"
#include "PARS/Util/DirectX12/d3dUtil.h"

namespace PARS
{
	ID3D12Resource* D3DUtil::CreateBufferResource(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const void* initData, UINT byteSize,
		D3D12_HEAP_TYPE heapType, D3D12_RESOURCE_STATES  resourceState, ID3D12Resource** uploadBuffer)
	{
		ID3D12Resource* buffer = nullptr;

		D3D12_HEAP_PROPERTIES heapProperties;
		ZeroMemory(&heapProperties, sizeof(heapProperties));
		heapProperties.Type = heapType;
		heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		heapProperties.CreationNodeMask = 1;
		heapProperties.VisibleNodeMask = 1;

		D3D12_RESOURCE_DESC resourceDesc;
		ZeroMemory(&resourceDesc, sizeof(resourceDesc));
		resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resourceDesc.Alignment = 0;
		resourceDesc.Width = byteSize;
		resourceDesc.Height = 1;
		resourceDesc.DepthOrArraySize = 1;
		resourceDesc.MipLevels = 1;
		resourceDesc.Format = DXGI_FORMAT_UNKNOWN;
		resourceDesc.SampleDesc.Count = 1;
		resourceDesc.SampleDesc.Quality = 0;
		resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
		resourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

		D3D12_RESOURCE_STATES resourceStates = D3D12_RESOURCE_STATE_COPY_DEST;
		if (heapType == D3D12_HEAP_TYPE_UPLOAD)
		{
			resourceStates = D3D12_RESOURCE_STATE_GENERIC_READ;
		}
		else if (heapType == D3D12_HEAP_TYPE_READBACK)
		{
			resourceStates = D3D12_RESOURCE_STATE_COPY_DEST;
		}

		HRESULT result = device->CreateCommittedResource(&heapProperties, D3D12_HEAP_FLAG_NONE,
			&resourceDesc, resourceStates, nullptr, IID_PPV_ARGS(&buffer));
		if (FAILED(result)) PARS_ERROR("Could not create Resource");

		if (initData != nullptr)
		{
			switch (heapType)
			{
			case D3D12_HEAP_TYPE_DEFAULT:
			{
				if (uploadBuffer != nullptr)
				{
					heapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;
					device->CreateCommittedResource(&heapProperties, D3D12_HEAP_FLAG_NONE, &resourceDesc,
						D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(uploadBuffer));

					D3D12_SUBRESOURCE_DATA subResourceData;
					ZeroMemory(&subResourceData, sizeof(D3D12_SUBRESOURCE_DATA));
					subResourceData.pData = initData;
					subResourceData.SlicePitch = subResourceData.RowPitch = byteSize;
					UpdateSubresources<1>(commandList, buffer, *uploadBuffer, 0, 0, 1, &subResourceData);

					D3D12_RESOURCE_BARRIER resourceBarrier;
					::ZeroMemory(&resourceBarrier, sizeof(D3D12_RESOURCE_BARRIER));
					resourceBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
					resourceBarrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
					resourceBarrier.Transition.pResource = buffer;
					resourceBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
					resourceBarrier.Transition.StateAfter = resourceState;
					resourceBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
					commandList->ResourceBarrier(1, &resourceBarrier);
				}
				break;
			}
			case D3D12_HEAP_TYPE_UPLOAD:
			{
				D3D12_RANGE readRange = { 0, 0 };
				UINT8* bufferDataBegin = nullptr;
				buffer->Map(0, &readRange, (void**)&bufferDataBegin);
				memcpy(bufferDataBegin, initData, byteSize);
				buffer->Unmap(0, nullptr);
				break;
			}
			case D3D12_HEAP_TYPE_READBACK:
				break;
			case D3D12_HEAP_TYPE_CUSTOM:
				break;
			}
		}

		return buffer;
	}
}