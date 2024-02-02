#pragma once
#include "../pch.h"
#include "graphics.h"
#include "globals.h"
#include "bindable.h"
#include <DirectXMath.h>

class VertexConstant : public Bindable
{
public:
	VertexConstant(Graphics& gfx, ConstantBuffer& constBuffer);
	void Bind(Graphics& gfx) override;
	void UpdateConstant(Graphics& gfx, ConstantBuffer& cb);

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_pBuffer;
};