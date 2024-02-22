#pragma once
#include "../pch.h"
#include "../asserts.h"
#include "graphics.h"
#include "bindable.h"

class IndexBuffer : public Bindable
{
public:
	IndexBuffer(Graphics& gfx, std::vector<USHORT>& buffer);
	IndexBuffer(Graphics& gfx, unsigned short* buffer, int indexCount);

	void Bind(Graphics& gfx) override;
	UINT GetSize() const;

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_pBuffer;
	UINT count;
	
};