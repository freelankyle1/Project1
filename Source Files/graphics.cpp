#include "Headers/pch.h"
#include "Headers/asserts.h"
#include "Headers/Rendering/graphics.h"
#include "Headers/Rendering/vertexbuffer.h"
#include "Headers/Rendering/indexbuffer.h"
#include "Headers/Rendering/shader.h"
#include "Headers/Rendering/inputlayout.h"
#include "Headers/Rendering/topology.h"
#include "Headers/Rendering/globals.h"
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "D3DCompiler.lib")

using namespace Microsoft::WRL;
using namespace DirectX;


Graphics::Graphics(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC scDesc = {};
	scDesc.BufferDesc.Width = 0;
	scDesc.BufferDesc.Height = 0;
	scDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	scDesc.BufferDesc.RefreshRate.Numerator = 0;
	scDesc.BufferDesc.RefreshRate.Denominator = 0;
	scDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scDesc.SampleDesc.Count = 1;
	scDesc.SampleDesc.Quality = 0;
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scDesc.BufferCount = 1;
	scDesc.OutputWindow = hWnd;
	scDesc.Windowed = TRUE;
	scDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scDesc.Flags = 0;

	HRESULT hr;


	hr = D3D11CreateDeviceAndSwapChain(
		nullptr, D3D_DRIVER_TYPE_HARDWARE,
		nullptr, D3D11_CREATE_DEVICE_DEBUG, nullptr,
		0, D3D11_SDK_VERSION,
		&scDesc, &m_SwapChain,
		&m_Device, nullptr, &m_DevContext);
	ASSERT(hr, "Create Device and Swap Chain");

	ComPtr<ID3D11Resource> pBackBuffer;
	hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer);
	ASSERT(hr, "Swap Chain Get Buffer");

	hr = m_Device->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &m_RTView);
	ASSERT(hr, "Create Render Target View");

	D3D11_DEPTH_STENCIL_DESC dsd = {};
	dsd.DepthEnable = TRUE;
	dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsd.DepthFunc = D3D11_COMPARISON_LESS;

	ComPtr<ID3D11DepthStencilState> pDState;
	hr = m_Device->CreateDepthStencilState(&dsd, &pDState);
	ASSERT(hr, "failed to create depth stencil state");
	
	m_DevContext->OMSetDepthStencilState(pDState.Get(), 1u);

	ComPtr<ID3D11Texture2D> pDepthStencil;
	D3D11_TEXTURE2D_DESC descDepth = {};
	descDepth.Width = (UINT)SCREEN_WIDTH;
	descDepth.Height = (UINT)SCREEN_HEIGHT;
	descDepth.MipLevels = 1u;
	descDepth.ArraySize = 1u;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1u;
	descDepth.SampleDesc.Quality = 0u;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	
	hr = m_Device->CreateTexture2D(&descDepth, nullptr, &pDepthStencil);
	ASSERT(hr, "failed to create depth stencil buffer");

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd = {};
	dsvd.Format = DXGI_FORMAT_D32_FLOAT;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvd.Texture2D.MipSlice = 0u;

	hr = m_Device->CreateDepthStencilView(pDepthStencil.Get(), &dsvd, &m_DsView);
	ASSERT(hr, "failed to create depth stencil view");

	m_DevContext->OMSetRenderTargets(1u, m_RTView.GetAddressOf(), m_DsView.Get());

	D3D11_VIEWPORT vp;
	vp.Width = SCREEN_WIDTH;
	vp.Height = SCREEN_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	m_DevContext->RSSetViewports(1, &vp);

}

void Graphics::EndFrame()
{
	m_SwapChain->Present(1u, 0u);
}

void Graphics::ClearBuffer(float r, float g, float b) noexcept
{
	const float color[] = { r,g,b,1.0 };
	m_DevContext->ClearRenderTargetView(m_RTView.Get(), color);
	m_DevContext->ClearDepthStencilView(m_DsView.Get(), D3D11_CLEAR_DEPTH,1.0f, 0);
}

void Graphics::DrawIndexed(UINT indexCount)
{
	m_DevContext->DrawIndexed(indexCount, 0u, 0);
}

void Graphics::SetProjection(DirectX::XMMATRIX proj)
{
	projection = proj;
}

DirectX::XMMATRIX Graphics::GetProjection() const
{
	return projection;
}

const ID3D11Device* const Graphics::GetDevice() const
{
	return m_Device.Get();
}
const ID3D11DeviceContext* const Graphics::GetContext() const
{
	return m_DevContext.Get();
}
