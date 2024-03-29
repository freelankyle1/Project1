#include "Headers/pch.h"
#include "Headers/Rendering/vertexbuffer.h"

VertexBuffer::VertexBuffer(Graphics& gfx, const std::vector<Vertex>& buffer)
	:m_Stride(sizeof(Vertex))
{
	D3D11_BUFFER_DESC m_BufferDesc = {};

	m_Offset = 0u;

	m_BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	m_BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	m_BufferDesc.CPUAccessFlags = 0u;
	m_BufferDesc.MiscFlags = 0u;
	m_BufferDesc.ByteWidth = sizeof(Vertex) * buffer.size();
	m_BufferDesc.StructureByteStride = sizeof(Vertex);

	D3D11_SUBRESOURCE_DATA m_SubresourceData = {};
	m_SubresourceData.pSysMem = buffer.data();

	HRESULT hr;
	hr = gfx.GetDevice()->CreateBuffer(&m_BufferDesc, &m_SubresourceData, &m_pBuffer);
	ASSERT(hr, "failed to create vertex buffer!");

}
VertexBuffer::VertexBuffer(Graphics& gfx, const VertexData* buffer, const int buffersize)
	:m_Stride(sizeof(VertexData))
{
	D3D11_BUFFER_DESC m_BufferDesc = {};

	m_Offset = 0u;

	m_BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	m_BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	m_BufferDesc.CPUAccessFlags = 0u;
	m_BufferDesc.MiscFlags = 0u;
	m_BufferDesc.ByteWidth = (UINT)(sizeof(VertexData) * buffersize);
	m_BufferDesc.StructureByteStride = sizeof(VertexData);

	D3D11_SUBRESOURCE_DATA m_SubresourceData = {};
	m_SubresourceData.pSysMem = buffer;

	HRESULT hr;
	hr = gfx.GetDevice()->CreateBuffer(&m_BufferDesc, &m_SubresourceData, &m_pBuffer);
	ASSERT(hr, "failed to create vertex buffer!");

}

void VertexBuffer::Bind(Graphics& gfx)
{
	gfx.GetContext()->IASetVertexBuffers(0u, 1u, m_pBuffer.GetAddressOf(), &m_Stride, &m_Offset);
}
