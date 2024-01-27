#include "pch.h"
#include "Headers/graphics.h"
#include "Headers/asserts.h"
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

}

void Graphics::EndFrame()
{
	m_SwapChain->Present(1u, 0u);
}

void Graphics::ClearBuffer(float r, float g, float b) noexcept
{
	const float color[] = { r,g,b,1.0 };
	m_DevContext->ClearRenderTargetView(m_RTView.Get(), color);
}

void Graphics::DrawTestTriangle(float angle, float x, float y, float color)
{
	HRESULT hr;

	struct Vertex
	{
		struct
		{
			float x;
			float y;
			float z;
		}pos;
		
	};

	const Vertex vertices[] =
	{
		{-1.0f, -1.0f,-1.0f},
		{ 1.0f, -1.0f,-1.0f},
		{-1.0f,  1.0f,-1.0f},
		{ 1.0f,  1.0f,-1.0f},
		{-1.0f, -1.0f, 1.0f},
		{ 1.0f, -1.0f, 1.0f},
		{-1.0f,  1.0f, 1.0f},
		{ 1.0f,  1.0f, 1.0f},

	};
	const unsigned short indices[] =
	{
		0,2,1, 2,3,1,
		1,3,5, 3,7,5,
		2,6,3, 3,6,7,
		4,5,7, 4,7,6,
		0,4,2, 2,4,6,
		0,1,4, 1,5,4
	};

	struct ConstantBuffer
	{
		XMMATRIX transform;
	};

	const ConstantBuffer cb =
	{
		{
			XMMatrixTranspose(
			XMMatrixRotationZ(angle)*
			XMMatrixRotationX(angle)*
			XMMatrixTranslation(x, y, 4.0f)*
			XMMatrixPerspectiveLH(1.0f, 0.5625f, 0.5f, 10.f)
			)
			
		}
	};


	ComPtr<ID3D11Buffer> pConstantBuffer;
	D3D11_BUFFER_DESC cbd;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.ByteWidth = sizeof(cb);
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0u;
	cbd.StructureByteStride = 0u;
	D3D11_SUBRESOURCE_DATA csd = {};
	csd.pSysMem = &cb;
	hr = m_Device->CreateBuffer(&cbd, &csd, &pConstantBuffer);
	ASSERT(hr, "Constant buffer creation failed!");

	using namespace Microsoft::WRL;
	ComPtr<ID3D11Buffer> pVertexBuffer;

	D3D11_BUFFER_DESC vDesc = {};
	vDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vDesc.Usage = D3D11_USAGE_DEFAULT;
	vDesc.CPUAccessFlags = 0u;
	vDesc.MiscFlags = 0u;
	vDesc.ByteWidth = sizeof(vertices);
	vDesc.StructureByteStride = sizeof(Vertex);

	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = vertices;

	UINT stride = sizeof(Vertex);
	UINT offset = 0u;

	hr = m_Device->CreateBuffer(&vDesc, &sd, &pVertexBuffer);
	ASSERT(hr, "create vertex buffer");

	
	m_DevContext->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);

	

	ComPtr<ID3D11Buffer> pIndexBuffer;
	D3D11_BUFFER_DESC ibd = {};
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.CPUAccessFlags = 0u;
	ibd.MiscFlags = 0u;
	ibd.ByteWidth = sizeof(indices);
	ibd.StructureByteStride = sizeof(unsigned short);
	D3D11_SUBRESOURCE_DATA isd = {};
	isd.pSysMem = indices;
	hr = m_Device->CreateBuffer(&ibd, &isd, &pIndexBuffer);
	ASSERT(hr, "creating index buffer failed");

	m_DevContext->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);

	ComPtr<ID3DBlob> pBlob;

	struct ConstantBuffer2
	{
		struct
		{
			float r;
			float g;
			float b;
			float a;
		}face_colors[6];
	};
	const ConstantBuffer2 cb2
	{
		{
			{1.0f,0.0f,1.0f},
			{1.0f,0.0f,0.0f},
			{0.0f,1.0f,0.0f},
			{0.0f,0.0f,1.0f},
			{1.0f,1.0f,0.0f},
			{0.0f,1.0f,1.0f},
		}
	};
	ComPtr<ID3D11Buffer> pConstantBuffer2;
	D3D11_BUFFER_DESC cbd2 = {};
	cbd2.ByteWidth = sizeof(cb2);
	cbd2.Usage = D3D11_USAGE_DYNAMIC;
	cbd2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd2.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd2.MiscFlags = 0u;
	cbd2.StructureByteStride = 0u;
	D3D11_SUBRESOURCE_DATA cb2r;
	cb2r.pSysMem = &cb2;

	hr = m_Device->CreateBuffer(&cbd2, &cb2r, pConstantBuffer2.GetAddressOf());
	ASSERT(hr, "failed to create constant buffer 2!");

	ComPtr<ID3D11PixelShader> pPixelShader;
	hr = D3DReadFileToBlob(L"PixelShader.cso", &pBlob);
	ASSERT(hr, "reading pixel shader to blob");
	hr = m_Device->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);
	ASSERT(hr, "Pixel shader creation failed!");
	//bind pixel shader!
	m_DevContext->PSSetShader(pPixelShader.Get(), 0, 0);

	m_DevContext->PSSetConstantBuffers(0u, 1u, pConstantBuffer2.GetAddressOf());
	
	ComPtr<ID3D11VertexShader> pVertexShader;
	hr = D3DReadFileToBlob(L"VertexShader.cso", &pBlob);
	ASSERT(hr, "readfile to blob - vertex shader");
	hr = m_Device->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);
	ASSERT(hr, "Vertex shader creation failed!");
	//bind vertex shader
	m_DevContext->VSSetShader(pVertexShader.Get(), 0, 0);

	
	//bind our constants
	m_DevContext->VSSetConstantBuffers(0, 1u, pConstantBuffer.GetAddressOf());

	


	//input (vertex) layout
	ComPtr<ID3D11InputLayout> pInputLayout;
	const D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{"Position", 0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
	};

	m_Device->CreateInputLayout(ied, (UINT)std::size(ied), pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pInputLayout);
	m_DevContext->IASetInputLayout(pInputLayout.Get());

	//bind render targets
	m_DevContext->OMSetRenderTargets(1u, m_RTView.GetAddressOf(), nullptr);

	m_DevContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3D11_VIEWPORT vp;
	vp.Width = 1280;
	vp.Height = 720;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	m_DevContext->RSSetViewports(1, &vp);


	m_DevContext->DrawIndexed((UINT)std::size(indices), 0u, 0u);
}
