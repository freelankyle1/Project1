#include "Headers/pch.h"
#include "Headers/shader.h"
#include "Headers/asserts.h"
#include "Headers/graphics.h"
#include <d3dcompiler.h>

//static std::unordered_map<const std::wstring, const Shader*> ShaderMap;
Microsoft::WRL::ComPtr<ID3DBlob> pBlob;

VertexShader::VertexShader(const std::wstring& filepath, const Graphics* gfx)
{
	m_gfx = gfx;
	m_Filepath = filepath.c_str();

	CompileShader();
	Bind();
}

void VertexShader::CompileShader()
{
	HRESULT hr;

	hr = D3DReadFileToBlob(m_Filepath, &pBlob);
	ASSERT(hr, "readfile to blob - vertex shader");

	hr = m_gfx->GetDevice()->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &m_pVertexShader);
	ASSERT(hr, "Vertex shader creation failed!");
}

void VertexShader::Bind() const
{
	m_gfx->GetContext()->VSSetShader(m_pVertexShader.Get(), 0, 0);
}


PixelShader::PixelShader(const std::wstring& filepath, const Graphics* gfx)
{
	m_gfx = gfx;
	m_Filepath = filepath.c_str();

	CompileShader();
	Bind();
}

void PixelShader::CompileShader()
{
	HRESULT hr;

	hr = D3DReadFileToBlob(m_Filepath, &pBlob);
	ASSERT(hr, "failed to read pixel shader to blob!");

	hr = m_gfx->GetDevice()->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), 0, &m_pPixelShader);
	ASSERT(hr, "failed to create pixel shader!");
}

void PixelShader::Bind() const
{
	m_gfx->GetContext()->PSSetShader(m_pPixelShader.Get(), 0, 0);
}