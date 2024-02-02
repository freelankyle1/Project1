#pragma once
#include "../pch.h"
#include "bindable.h"

class Graphics;

class VertexShader : public Bindable
{
public:
	VertexShader(Graphics& gfx, const std::wstring& filepath);
	void Bind(Graphics& gfx) override;
	ID3DBlob* GetByteCode() const;

private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_pVertexShader;
	LPCWSTR m_Filepath;
	Microsoft::WRL::ComPtr<ID3DBlob> m_pBlob;

};

class PixelShader : public Bindable
{
public:
	PixelShader(Graphics& gfx, const std::wstring& filepath);
	void Bind(Graphics& gfx) override;

private:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pPixelShader;
	LPCWSTR m_Filepath;
};