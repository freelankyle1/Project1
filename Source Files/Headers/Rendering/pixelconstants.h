#pragma once
#include "../pch.h"
#include "graphics.h"
#include "globals.h"
#include "bindable.h"
#include <DirectXMath.h>

class PixelConstant : public Bindable
{
public:
	PixelConstant(Graphics& gfx, ConstantBuffer2& constBuffer);
	void Bind(Graphics& gfx) override;

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_pBuffer;
};