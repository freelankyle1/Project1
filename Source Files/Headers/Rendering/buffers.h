#pragma once
#include "../pch.h"
#include <d3dcompiler.h>
#include "buffer.h"

struct Vertex
{
	struct
	{
		float x;
		float y;
		float z;
	}pos;

};

class VertexBuffer : public Buffer
{
public:
	VertexBuffer() = default; //create the vertex buffer
	VertexBuffer(std::vector<Vertex>& buffer);
	void CreateBuffer(const Graphics& gfx) override;
	void Bind(const Graphics& gfx) override; //bind the vertex buffer
	~VertexBuffer() = default;
	
private:
	std::vector<Vertex> m_VertexBuffer;
	UINT m_Stride;
	UINT m_Offset;
	
};

class IndexBuffer : public Buffer
{
public:
	IndexBuffer() = default;
	IndexBuffer(std::vector<USHORT>& buffer);
	void CreateBuffer(const Graphics& gfx) override;
	void Bind(const Graphics& gfx) override;
	UINT GetSize() const;
	~IndexBuffer() = default;

private:
	std::vector<USHORT> m_IndexBuffer;
};

class ConstantBuffer : public Buffer
{
public:
	ConstantBuffer() = default;
	void CreateBuffer(const Graphics& gfx) override;
	void Bind(const Graphics& gfx) override;
	~ConstantBuffer() = default;
};

class DepthBuffer : public Buffer
{
	DepthBuffer() = default;
	void CreateBuffer(const Graphics& gfx) override;
	void Bind(const Graphics& gfx) override;
	~DepthBuffer() = default;
};