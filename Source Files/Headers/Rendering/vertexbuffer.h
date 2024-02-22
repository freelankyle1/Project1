#pragma once
#include "../pch.h"
#include "../asserts.h"
#include "globals.h"
#include "graphics.h"
#include "bindable.h"



class VertexBuffer : public Bindable
{
public:
	VertexBuffer(Graphics& gfx, const std::vector<Vertex>& buffer);
	VertexBuffer(Graphics& gfx, const VertexData* buffer, const int buffersize);
	void Bind(Graphics& gfx) override;
	
private:
	UINT m_Stride;
	UINT m_Offset;

	Microsoft::WRL::ComPtr<ID3D11Buffer> m_pBuffer;
	
};
