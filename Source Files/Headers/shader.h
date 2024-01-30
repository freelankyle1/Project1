#pragma once
#include "pch.h"

class Graphics;

class Shader
{
public:
	
private:
	virtual void Bind() const = 0;
	virtual void CompileShader() = 0;

private:
	//data storage for all the shaders
	

};

class VertexShader : public Shader
{
public:
	VertexShader(const std::wstring& filepath, const Graphics* gfx);
	~VertexShader() = default;

private:
	void Bind() const override;
	void CompileShader() override;

private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_pVertexShader;
	LPCWSTR m_Filepath;
	const Graphics* m_gfx;

};


class PixelShader : public Shader
{
public:
	PixelShader(const std::wstring& filepath, const Graphics* gfx);
	~PixelShader() = default;
private:
	void Bind() const override;
	void CompileShader() override;

private:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pPixelShader;
	LPCWSTR m_Filepath;
	const Graphics* m_gfx;
};