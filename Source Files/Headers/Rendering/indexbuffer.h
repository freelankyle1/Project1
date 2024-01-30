#pragma once
#include "../pch.h"
#include "../asserts.h"
#include "bindable.h"

class IndexBuffer : public Bindable
{
public:
	IndexBuffer(std::vector<USHORT>& buffer, Graphics& gfx);
	void CreateBuffer(const Graphics& gfx);
	void Bind(Graphics& gfx) const override;
	UINT GetSize() const;
	

private:
	std::vector<USHORT> m_IndexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_pBuffer;
	D3D11_BUFFER_DESC m_BufferDesc;
	D3D11_SUBRESOURCE_DATA m_SubresourceData;
};