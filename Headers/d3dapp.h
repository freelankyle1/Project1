#pragma once
#include "../pch.h"

class d3dApp
{
public:
	d3dApp(HWND);
	void appInit();

private:

	void swapChainInit();
	void initRenderView();
	void depthStencilInit();

private:

	//used to check feature support, and allocate resources
	ID3D11Device* mAppDevice;
	//used to set render states, bind resources to the graphics pipeline, and issue rendering commands
	ID3D11DeviceContext* mDeviceContextIm;

	//description of our swap chain
	DXGI_SWAP_CHAIN_DESC mScDesc;
	//actual pointer to the swap chain interface
	IDXGISwapChain* mSwapChain;
	
	//interface that defines the render-target subresources that can be accessed during rendering
	ID3D11RenderTargetView* mRtView;
	//pointer to the back buffer
	ID3D11Texture2D* mBackBuffer;
	
	D3D11_TEXTURE2D_DESC mDSDesc;
	ID3D11Texture2D* mDepthStencilBuffer;
	ID3D11DepthStencilView* mDepthStencilView;

	D3D11_VIEWPORT mViewport;

	UINT m4xMsaaQuality;
	HWND mHwnd;


	
};