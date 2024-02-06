#include "Headers/pch.h"
#include "Headers/Rendering/indexbuffer.h"

IndexBuffer::IndexBuffer(Graphics& gfx, std::vector<USHORT>& buffer)
	: count(buffer.size())
{
	D3D11_BUFFER_DESC m_BufferDesc = {};

	m_BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	m_BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	m_BufferDesc.CPUAccessFlags = 0u;
	m_BufferDesc.MiscFlags = 0u;
	m_BufferDesc.ByteWidth = static_cast<UINT>(count * sizeof(USHORT));
	m_BufferDesc.StructureByteStride = sizeof(USHORT);

	D3D11_SUBRESOURCE_DATA m_SubresourceData = {};
	m_SubresourceData.pSysMem = buffer.data();
	
	HRESULT hr;
	hr = gfx.GetDevice()->CreateBuffer(&m_BufferDesc, &m_SubresourceData, &m_pBuffer);
	ASSERT(hr, "failed to create index buffer!");

}

void IndexBuffer::Bind(Graphics& gfx)
{
	gfx.GetContext()->IASetIndexBuffer(m_pBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
}


//required for draw indexed I guess?
UINT IndexBuffer::GetSize() const
{
	return count;
}