#pragma once
#include "../pch.h"
#include "../asserts.h"
#include "bindable.h"
#include <d3dcompiler.h>

//extern Microsoft::WRL::ComPtr<ID3DBlob> pBlob;

class InputLayout : public Bindable
{
public:
	InputLayout(std::vector<D3D11_INPUT_ELEMENT_DESC>& input, Graphics& gfx);
	void CreateInputLayout(const std::vector<D3D11_INPUT_ELEMENT_DESC>& input, Graphics& gfx);
	void Bind(Graphics& gfx) const;

private:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout;
};