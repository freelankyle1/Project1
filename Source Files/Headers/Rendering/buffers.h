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
	VertexBuffer(std::vector<Vertex>& buffer, const Graphics* gfx);
	void CreateBuffer(const Graphics& gfx) override;
	void Bind(const Graphics& gfx) const override; //bind the vertex buffer
	~VertexBuffer() = default;
	
private:
	const Graphics* gfx;
	std::vector<Vertex> m_VertexBuffer;
	UINT m_Stride;
	UINT m_Offset;
	
};

class IndexBuffer : public Buffer
{
public:
	IndexBuffer() = default;
	IndexBuffer(std::vector<USHORT>& buffer, const Graphics* gfx);
	void CreateBuffer(const Graphics& gfx) override;
	void Bind(const Graphics& gfx) const override;
	UINT GetSize() const;
	~IndexBuffer() = default;

private:
	const Graphics* gfx;
	std::vector<USHORT> m_IndexBuffer;
};

class ConstantBuffer : public Buffer
{
public:
	ConstantBuffer() = default;
	void CreateBuffer(const Graphics& gfx) override;
	void Bind(const Graphics& gfx) const override;
	~ConstantBuffer() = default;

private:
	const Graphics* gfx;

};

class DepthBuffer : public Buffer
{
	DepthBuffer() = default;
	void CreateBuffer(const Graphics& gfx) override;
	void Bind(const Graphics& gfx) const override;
	~DepthBuffer() = default;

private:
	const Graphics* gfx;

};