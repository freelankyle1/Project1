#pragma once
#include "../pch.h"
#include "Headers/graphics.h"
#include <d3dcompiler.h>


class Buffer
{
public:
	virtual void Bind(const Graphics& gfx) const  = 0;
	virtual void CreateBuffer(const Graphics& gfx) = 0;
public:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_pBuffer;
	D3D11_BUFFER_DESC m_BufferDesc;
	D3D11_SUBRESOURCE_DATA m_SubresourceData;
};