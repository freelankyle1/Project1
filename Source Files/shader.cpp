#include "Headers/pch.h"
#include "Headers/asserts.h"
#include "Headers/Rendering/shader.h"
#include "Headers/Rendering/graphics.h"
#include <d3dcompiler.h>



VertexShader::VertexShader(Graphics& gfx, const std::wstring& filepath)
{
	m_Filepath = filepath.c_str();

	HRESULT hr;

	hr = D3DReadFileToBlob(m_Filepath, &m_pBlob);
	ASSERT(hr, "readfile to blob - vertex shader");

	
	hr = gfx.m_Device->CreateVertexShader(m_pBlob->GetBufferPointer(), m_pBlob->GetBufferSize(), nullptr, &m_pVertexShader);
	ASSERT(hr, "Vertex shader creation failed!");

	ASSERT_INFO(filepath.c_str());

}

void VertexShader::Bind(Graphics& gfx)
{
	gfx.m_DevContext->VSSetShader(m_pVertexShader.Get(), 0, 0);

}

ID3DBlob* VertexShader::GetByteCode() const
{
	return m_pBlob.Get();
}


PixelShader::PixelShader(Graphics& gfx, const std::wstring& filepath)
{
	m_Filepath = filepath.c_str();
	
	HRESULT hr;

	Microsoft::WRL::ComPtr <ID3DBlob> pBlob2;

	hr = D3DReadFileToBlob(m_Filepath, &pBlob2);
	ASSERT(hr, "failed to read pixel shader to blob!");

	hr = gfx.m_Device->CreatePixelShader(pBlob2->GetBufferPointer(), pBlob2->GetBufferSize(), 0, &m_pPixelShader);
	ASSERT(hr, "failed to create pixel shader!");

}

void PixelShader::Bind(Graphics& gfx)
{
	gfx.m_DevContext->PSSetShader(m_pPixelShader.Get(), 0, 0);

}
