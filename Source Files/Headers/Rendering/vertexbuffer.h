#pragma once
#include "../pch.h"
#include "../asserts.h"
#include "globals.h"
#include "graphics.h"
#include "bindable.h"


//Buffers ARE Bindables - Buffer Inherits Bindable
//Reason for templating this class:
//So vertex buffers can be filled with a vector of:
//Vec3s, Vec4s, etc
class VertexBuffer : public Bindable
{
public:
	VertexBuffer(Graphics& gfx, const std::vector<Vertex>& buffer);
	void Bind(Graphics& gfx) override;
	
private:
	UINT m_Stride;
	UINT m_Offset;

	Microsoft::WRL::ComPtr<ID3D11Buffer> m_pBuffer;
	
};
