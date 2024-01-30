#pragma once
#include "../pch.h"
#include "../timer.h"
#include "../d3dexception.h"

class Graphics : public NonCopyable
{
	friend class Bindable;
public:
	Graphics(HWND);
	~Graphics() = default;
	void EndFrame();
	void ClearBuffer(float r, float g, float b) noexcept;
	void DrawTestTriangle(float angle,float x,float y, float col);
	void DrawIndexed(UINT indexCount);


private:
	Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_DevContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RTView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_DsView;
};