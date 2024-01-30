#include "Headers/pch.h"
#include "Headers/asserts.h"
#include "Headers/Rendering/shader.h"
#include "Headers/Rendering/graphics.h"
#include <d3dcompiler.h>

//static std::unordered_map<const std::wstring, const Shader*> ShaderMap;
Microsoft::WRL::ComPtr<ID3DBlob> pBlob;

VertexShader::VertexShader(const std::wstring& filepath, Graphics& gfx)
{
	m_Filepath = filepath.c_str();

	CompileShader(gfx);
	Bind(gfx);
}

void VertexShader::CompileShader(Graphics& gfx)
{
	HRESULT hr;

	hr = D3DReadFileToBlob(m_Filepath, &pBlob);
	ASSERT(hr, "readfile to blob - vertex shader");

	hr = GetDevice(gfx)->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &m_pVertexShader);
	ASSERT(hr, "Vertex shader creation failed!");
}

void VertexShader::Bind(Graphics& gfx) const
{
	GetContext(gfx)->VSSetShader(m_pVertexShader.Get(), 0, 0);
}


PixelShader::PixelShader(const std::wstring& filepath, Graphics& gfx)
{
	m_Filepath = filepath.c_str();

	CompileShader(gfx);
	Bind(gfx);
}

void PixelShader::CompileShader(Graphics& gfx)
{
	HRESULT hr;

	hr = D3DReadFileToBlob(m_Filepath, &pBlob);
	ASSERT(hr, "failed to read pixel shader to blob!");

	hr = GetDevice(gfx)->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), 0, &m_pPixelShader);
	ASSERT(hr, "failed to create pixel shader!");
}

void PixelShader::Bind(Graphics& gfx) const
{
	GetContext(gfx)->PSSetShader(m_pPixelShader.Get(), 0, 0);
}