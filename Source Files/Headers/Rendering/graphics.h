#pragma once
#include "../pch.h"
#include "../timer.h"
#include "../d3dexception.h"
#include "shader.h"
#include "renderer2d.h"
#include <DirectXMath.h>

class Graphics : public NonCopyable
{
public:
	Graphics(HWND);
	~Graphics() = default;
	void EndFrame();
	void ClearBuffer(float r, float g, float b) noexcept;
	void DrawIndexed(UINT indexCount);

	void SetProjection(DirectX::XMMATRIX proj);
	DirectX::XMMATRIX GetProjection() const;
	
	ID3D11Device* GetDevice() const;
	ID3D11DeviceContext* GetContext() const;

private:
	Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_DevContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RTView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_DsView;

	DirectX::XMMATRIX projection;
	
	friend class Renderer2D;
};