#include "Headers/pch.h"
#include "Headers/Rendering/inputlayout.h"

extern Microsoft::WRL::ComPtr<ID3DBlob> pBlob;

InputLayout::InputLayout(std::vector<D3D11_INPUT_ELEMENT_DESC>& input, Graphics& gfx)
{
	CreateInputLayout(input, gfx);
	Bind(gfx);
}

void InputLayout::CreateInputLayout(const std::vector<D3D11_INPUT_ELEMENT_DESC>& input, Graphics& gfx)
{
	HRESULT hr;
	hr = GetDevice(gfx)->CreateInputLayout(&input[0], (UINT)input.size(), pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &m_pInputLayout);
	ASSERT(hr, "failed to create input layout!");
}

void InputLayout::Bind(Graphics& gfx) const
{
	GetContext(gfx)->IASetInputLayout(m_pInputLayout.Get());
}
