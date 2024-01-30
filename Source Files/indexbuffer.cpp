#include "Headers/pch.h"
#include "Headers/Rendering/indexbuffer.h"

IndexBuffer::IndexBuffer(std::vector<USHORT>& buffer, Graphics& gfx)
{
	m_IndexBuffer = std::move(buffer);

	m_BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	m_BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	m_BufferDesc.CPUAccessFlags = 0u;
	m_BufferDesc.MiscFlags = 0u;
	m_BufferDesc.ByteWidth = static_cast<UINT>(m_IndexBuffer.size()) * sizeof(USHORT);
	m_BufferDesc.StructureByteStride = sizeof(USHORT);

	m_SubresourceData.pSysMem = m_IndexBuffer.data();
	CreateBuffer(gfx);
	Bind(gfx);
}

void IndexBuffer::CreateBuffer(const Graphics& gfx)
{
	HRESULT hr;
	hr = GetDevice(gfx)->CreateBuffer(&m_BufferDesc, &m_SubresourceData, &m_pBuffer);
	ASSERT(hr, "failed to create index buffer!");
}

void IndexBuffer::Bind(Graphics& gfx) const 
{
	GetContext(gfx)->IASetIndexBuffer(m_pBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
}

//required for draw indexed I guess?
UINT IndexBuffer::GetSize() const
{
	return (UINT)m_IndexBuffer.size();
}