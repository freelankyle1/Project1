#include "pch.h"
#include "Headers/window.h"

void d3dInit(HWND);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	try
	{
		window w(SCREEN_WIDTH, SCREEN_HEIGHT, "blah");


		//init d3d

		d3dInit(w.getHandle());

		MSG msg = { 0 };

		while (msg.message != WM_QUIT)
		{
			while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		
		return msg.wParam;
	}
	catch (const parentException& e)
	{
		MessageBox(nullptr, e.what(), e.getType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e)
	{
		MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, "No details available", "unknown exception", MB_OK | MB_ICONEXCLAMATION);
	}
}


//probably put into a renderer class
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

	if (m4xMsaaQuality)
	{
		sd.SampleDesc.Count = 4;
		sd.SampleDesc.Quality = m4xMsaaQuality - 1;
	}
	else
	{
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
	}

	IDXGIDevice* dxgiDevice = 0;
	d3ddevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);

	IDXGIAdapter* dxgiAdapter = 0;
	dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter);

	IDXGIFactory* dxgiFactory = 0;
	dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory);
	
	IDXGISwapChain* swapChain;

	dxgiFactory->CreateSwapChain(d3ddevice, &sd, &swapChain);

	dxgiDevice->Release();
	dxgiAdapter->Release();
	dxgiFactory->Release();

	//create a view so we can render to the back buffer of the swap chain

	ID3D11RenderTargetView* rtView;
	ID3D11Texture2D* backbuffer;
	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backbuffer);


	d3ddevice->CreateRenderTargetView(backbuffer,NULL, &rtView);

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

//performance timing

void timing()
{
	INT64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*) & currTime);

	INT64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);

	INT64 secondsPerCount = 1.0 / (DOUBLE)countsPerSec;







}