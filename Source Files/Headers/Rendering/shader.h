#pragma once
#include "../pch.h"
#include "bindable.h"

class Graphics;

class VertexShader : public Bindable
{
public:
	VertexShader(const std::wstring& filepath, Graphics& gfx);
	~VertexShader() = default;

private:
	void Bind(Graphics& gfx) const override;
	void CompileShader(Graphics& gfx);

private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_pVertexShader;
	LPCWSTR m_Filepath;

};

class PixelShader : public Bindable
{
public:
	PixelShader(const std::wstring& filepath, Graphics& gfx);
	~PixelShader() = default;
private:
	void Bind(Graphics& gfx) const override;
	void CompileShader(Graphics& gfx);

private:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pPixelShader;
	LPCWSTR m_Filepath;
	const Graphics* m_gfx;
};