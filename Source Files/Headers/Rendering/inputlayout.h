#pragma once
#include "../pch.h"
#include "../asserts.h"
#include "shader.h"
#include "graphics.h"
#include "bindable.h"
#include <d3dcompiler.h>

//extern Microsoft::WRL::ComPtr<ID3DBlob> pBlob;

class InputLayout : public Bindable
{
public:
	InputLayout(Graphics& gfx, const std::vector<D3D11_INPUT_ELEMENT_DESC>& input, ID3DBlob* bc);
	void Bind(Graphics& gfx) override;

private:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout;
};