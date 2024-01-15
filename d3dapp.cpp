#include "pch.h"
#include "Headers/d3dapp.h"
#include "Headers/window.h"


D3D_FEATURE_LEVEL featureLevels[4] =
{
	D3D_FEATURE_LEVEL_11_0, // First check D3D 11 support
	D3D_FEATURE_LEVEL_10_1, // Second check D3D 10.1 support
	D3D_FEATURE_LEVEL_10_0, // Next, check D3D 10 support
	D3D_FEATURE_LEVEL_9_3 // Finally, check D3D 9.3 support
};

d3dApp::d3dApp(HWND hWnd)
	: mHwnd(hWnd), mAppDevice(nullptr), mDeviceContextIm(nullptr), mSwapChain(nullptr),
	mRtView(nullptr), mBackBuffer(nullptr), mDepthStencilBuffer(nullptr), mDepthStencilView(nullptr),
	mScDesc({0}), mDSDesc({0}), mViewport({0})
{
	assert(D3D11CreateDevice
	(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL,D3D11_CREATE_DEVICE_DEBUG, NULL, 0,
	D3D11_SDK_VERSION, &mAppDevice, featureLevels, &mDeviceContextIm) == S_OK);

	mAppDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m4xMsaaQuality);
	assert(m4xMsaaQuality > 0);

}

void d3dApp::appInit()
{
	swapChainInit();
	initRenderView();
	depthStencilInit();
}

void d3dApp::swapChainInit()
{
	mScDesc.OutputWindow = mHwnd;
	mScDesc.Windowed = TRUE;
	mScDesc.BufferDesc.Width = SCREEN_WIDTH;
	mScDesc.BufferDesc.Height = SCREEN_HEIGHT;
	mScDesc.BufferDesc.RefreshRate.Numerator = 60;
	mScDesc.BufferDesc.RefreshRate.Denominator = 1;
	mScDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	mScDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	mScDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	mScDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	mScDesc.BufferCount = 1;
	mScDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	mScDesc.Flags = 0;

	if (m4xMsaaQuality)
	{
		mScDesc.SampleDesc.Count = 4;
		mScDesc.SampleDesc.Quality = m4xMsaaQuality - 1;
	}
	else
	{
		mScDesc.SampleDesc.Count = 1;
		mScDesc.SampleDesc.Quality = 0;
	}

	IDXGIDevice* dxgiDevice = 0;
	mAppDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);

	IDXGIAdapter* dxgiAdapter = 0;
	dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter);

	IDXGIFactory* dxgiFactory = 0;
	dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory);

	dxgiFactory->CreateSwapChain(mAppDevice, &mScDesc, &mSwapChain);

	dxgiDevice->Release();
	dxgiAdapter->Release();
	dxgiFactory->Release();

}

void d3dApp::initRenderView()
{
	mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&mBackBuffer);
	mAppDevice->CreateRenderTargetView(mBackBuffer, NULL, &mRtView);
}

void d3dApp::depthStencilInit()
{

	mDSDesc.Usage = D3D11_USAGE_DEFAULT;
	mDSDesc.Width = SCREEN_WIDTH;
	mDSDesc.Height = SCREEN_HEIGHT;
	mDSDesc.MipLevels = 1;
	mDSDesc.ArraySize = 1;
	mDSDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	if (m4xMsaaQuality)
	{
		mDSDesc.SampleDesc.Count = 4;
		mDSDesc.SampleDesc.Quality = m4xMsaaQuality - 1;
	}
	else
	{
		mDSDesc.SampleDesc.Count = 1;
		mDSDesc.SampleDesc.Quality = 0;
	}

	mDSDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	mDSDesc.CPUAccessFlags = 0;
	mDSDesc.MiscFlags = 0;

	
	assert(mAppDevice->CreateTexture2D(&mDSDesc, NULL, &mDepthStencilBuffer));
	assert(mAppDevice->CreateDepthStencilView(mDepthStencilBuffer, NULL, &mDepthStencilView));

	mDeviceContextIm->OMSetRenderTargets(1, &mRtView, mDepthStencilView);

	mViewport.MaxDepth = 1;
	mViewport.MinDepth = 0;
	mViewport.Width = (FLOAT)SCREEN_WIDTH;
	mViewport.Height = (FLOAT)SCREEN_HEIGHT;
	mViewport.TopLeftX = 0.0f;
	mViewport.TopLeftY = 0.0f;

	mDeviceContextIm->RSSetViewports(1, &mViewport);
}

//probably put into a renderer class
/*
void d3dInit(HWND hWnd)
{
	D3D_FEATURE_LEVEL featureLevels[4] =
	{
		D3D_FEATURE_LEVEL_11_0, // First check D3D 11 support
		D3D_FEATURE_LEVEL_10_1, // Second check D3D 10.1 support
		D3D_FEATURE_LEVEL_10_0, // Next, check D3D 10 support
		D3D_FEATURE_LEVEL_9_3 // Finally, check D3D 9.3 support
	};

	//create the device and the context

	ID3D11Device* d3ddevice; // used to check feature support, and allocate resources

	//used to set render states, bind resources to the graphics pipeline, and issue rendering commands
	ID3D11DeviceContext* d3dDeviceContextImmediate;

	assert(D3D11CreateDevice
	(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL,
		D3D11_CREATE_DEVICE_DEBUG, NULL, 0,
		D3D11_SDK_VERSION, &d3ddevice, featureLevels,
		&d3dDeviceContextImmediate) == S_OK);

	UINT m4xMsaaQuality;
	d3ddevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m4xMsaaQuality);
	assert(m4xMsaaQuality > 0);
	//describe the swap chain

	DXGI_SWAP_CHAIN_DESC sd;

	sd.OutputWindow = hWnd;
	sd.Windowed = TRUE;
	sd.BufferDesc.Width = SCREEN_WIDTH;
	sd.BufferDesc.Height = SCREEN_HEIGHT;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	

	//create a view so we can render to the back buffer of the swap chain

	mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&mBackBuffer);


	d3ddevice->CreateRenderTargetView(backbuffer, NULL, &rtView);


	D3D11_TEXTURE2D_DESC depthStencilDesc;

	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.Width = SCREEN_WIDTH;
	depthStencilDesc.Height = SCREEN_HEIGHT;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	if (m4xMsaaQuality)
	{
		depthStencilDesc.SampleDesc.Count = 4;
		depthStencilDesc.SampleDesc.Quality = m4xMsaaQuality - 1;
	}
	else
	{
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
	}

	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	ID3D11Texture2D* depthStencilBuffer;
	ID3D11DepthStencilView* depthStencilView;

	assert(d3ddevice->CreateTexture2D(&depthStencilDesc, NULL, &depthStencilBuffer));
	assert(d3ddevice->CreateDepthStencilView(depthStencilBuffer, NULL, &depthStencilView));

	d3dDeviceContextImmediate->OMSetRenderTargets(1, &rtView, depthStencilView);

	D3D11_VIEWPORT d3dViewport;
	d3dViewport.MaxDepth = 1;
	d3dViewport.MinDepth = 0;
	d3dViewport.Width = (FLOAT)SCREEN_WIDTH;
	d3dViewport.Height = (FLOAT)SCREEN_HEIGHT;
	d3dViewport.TopLeftX = 0.0f;
	d3dViewport.TopLeftY = 0.0f;

	d3dDeviceContextImmediate->RSSetViewports(1, &d3dViewport);

}
	*/

