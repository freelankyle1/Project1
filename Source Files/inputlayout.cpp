#include "Headers/pch.h"
#include "Headers/Rendering/inputlayout.h"


InputLayout::InputLayout(Graphics& gfx, const std::vector<D3D11_INPUT_ELEMENT_DESC>& input, ID3DBlob* bc)
{

	HRESULT hr;
	hr = gfx.m_Device->CreateInputLayout(input.data(), input.size(), bc->GetBufferPointer(), bc->GetBufferSize(), &m_pInputLayout);
	ASSERT(hr, "failed to create input layout!");

}

void InputLayout::Bind(Graphics& gfx)
{
	gfx.m_DevContext->IASetInputLayout(m_pInputLayout.Get());
}