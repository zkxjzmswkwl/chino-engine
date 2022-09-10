#pragma once
#include "Window.h"
#include <d3d11.h>

class Renderer
{
public:
	Renderer(Window& window);
	void BeginFrame();
	void EndFrame();
	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetContext();

private:
	void CreateDevice(Window& window);
	void CreateRenderTarget();

	IDXGISwapChain*      m_pSwapChain     = nullptr;
	ID3D11Device*        m_pDevice        = nullptr;
	ID3D11DeviceContext* m_pDeviceContext = nullptr;

	// Render target
	ID3D11RenderTargetView* m_pRenderTargetView = nullptr;
	D3D11_TEXTURE2D_DESC m_backBufferDesc;
};

