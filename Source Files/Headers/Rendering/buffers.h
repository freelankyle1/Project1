#pragma once
#include "../pch.h"
#include "../asserts.h"
#include "buffer.h"


//Buffers ARE Bindables - Buffer Inherits Bindable
//Reason for templating this class:
//So vertex buffers can be filled with a vector of:
//Vec3s, Vec4s, etc
template <typename t>
class VertexBuffer : public Bindable
{
public:
	VertexBuffer(std::vector<t>& buffer, Graphics& gfx)
	{
		m_Stride = sizeof(t);
		m_Offset = 0u;
		m_VertexBuffer = std::move(buffer);

		m_BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		m_BufferDesc.Usage = D3D11_USAGE_DEFAULT;
		m_BufferDesc.CPUAccessFlags = 0u;
		m_BufferDesc.MiscFlags = 0u;
		m_BufferDesc.ByteWidth = static_cast<UINT>(m_VertexBuffer.size()) * sizeof(t);
		m_BufferDesc.StructureByteStride = sizeof(t);

		m_SubresourceData.pSysMem = m_VertexBuffer.data();

		CreateBuffer(gfx);
		Bind(gfx);
	}

	void CreateBuffer(const Graphics& gfx)
	{
		HRESULT hr;
		hr = GetDevice(gfx)->CreateBuffer(&m_BufferDesc, &m_SubresourceData, &m_pBuffer);
		ASSERT(hr, "failed to create vertex buffer!");
	}

	void Bind(Graphics& gfx) const override
	{
		GetContext(gfx)->IASetVertexBuffers(0u, 1u, m_pBuffer.GetAddressOf(), &m_Stride, &m_Offset);
	}
private:
	std::vector<t> m_VertexBuffer;
	UINT m_Stride;
	UINT m_Offset;

	Microsoft::WRL::ComPtr<ID3D11Buffer> m_pBuffer;
	D3D11_BUFFER_DESC m_BufferDesc;
	D3D11_SUBRESOURCE_DATA m_SubresourceData;
	
};

/*
class IndexBuffer : public Bindable
{
public:
	IndexBuffer(std::vector<t>& buffer, Graphics& gfx)
	{
		m_IndexBuffer = std::move(buffer);

		m_BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		m_BufferDesc.Usage = D3D11_USAGE_DEFAULT;
		m_BufferDesc.CPUAccessFlags = 0u;
		m_BufferDesc.MiscFlags = 0u;
		m_BufferDesc.ByteWidth = static_cast<UINT>(m_IndexBuffer.size()) * sizeof(t);
		m_BufferDesc.StructureByteStride = sizeof(t);

		m_SubresourceData.pSysMem = m_IndexBuffer.data();
		CreateBuffer(gfx);
		Bind(gfx);
	}

	void CreateBuffer(const Graphics& gfx)
	{
		HRESULT hr;
		hr = GetDevice(gfx)->CreateBuffer(&m_BufferDesc, &m_SubresourceData, &m_pBuffer);
		ASSERT(hr, "failed to create index buffer!");
	}

	void Bind(Graphics& gfx) const override
	{
		GetContext(gfx)->IASetIndexBuffer(m_pBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
	}

	//required for draw indexed I guess?
	UINT GetSize() const
	{
		return (UINT)m_IndexBuffer.size();
	}


private:
	std::vector<t> m_IndexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_pBuffer;
	D3D11_BUFFER_DESC m_BufferDesc;
	D3D11_SUBRESOURCE_DATA m_SubresourceData;
};
*/

template <typename c>
class TransConstantBuffer : public Bindable
{
public:
	TransConstantBuffer(c& cb, Graphics& gfx)
	{
		m_BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		m_BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		m_BufferDesc.ByteWidth = sizeof(cb);
		m_BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		m_BufferDesc.MiscFlags = 0u;
		m_BufferDesc.StructureByteStride = 0u;

		m_SubresourceData.pSysMem = &cb;

		CreateBuffer(gfx);
		Bind(gfx);
	}

	void CreateBuffer(const Graphics& gfx)
	{
		HRESULT hr;
		hr = GetDevice(gfx)->CreateBuffer(&m_BufferDesc, &m_SubresourceData, &m_pBuffer);
		ASSERT(hr, "failed to create buffer!");
	}

	void Bind(Graphics& gfx) const override
	{
		GetContext(gfx)->VSSetConstantBuffers(0, 1u, m_pBuffer.GetAddressOf());
	}
	
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_pBuffer;
	D3D11_BUFFER_DESC m_BufferDesc;
	D3D11_SUBRESOURCE_DATA m_SubresourceData;
};

template <typename c>
class ConstBuffer : public Bindable
{
public:
	ConstBuffer(c& cb, Graphics& gfx)
	{

		m_BufferDesc.ByteWidth = sizeof(cb);
		m_BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		m_BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		m_BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		m_BufferDesc.MiscFlags = 0u;
		m_BufferDesc.StructureByteStride = 0u;
		D3D11_SUBRESOURCE_DATA cb2r;
		m_SubresourceData.pSysMem = &cb;

		CreateBuffer(gfx);
		Bind(gfx);

	}

	void CreateBuffer(const Graphics& gfx)
	{
		HRESULT hr;
		hr = GetDevice(gfx)->CreateBuffer(&m_BufferDesc, &m_SubresourceData, &m_pBuffer);
		ASSERT(hr, "failed to create constant buffer!");
	}

	void Bind(Graphics& gfx) const override
	{
		GetContext(gfx)->PSSetConstantBuffers(0u, 1u, m_pBuffer.GetAddressOf());
	}

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_pBuffer;
	D3D11_BUFFER_DESC m_BufferDesc;
	D3D11_SUBRESOURCE_DATA m_SubresourceData;
};
