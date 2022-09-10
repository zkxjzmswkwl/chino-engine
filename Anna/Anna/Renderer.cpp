#include "pch.h"
#include "Renderer.h"

Renderer::Renderer(Window& window)
{
	this->CreateDevice(window);
	this->CreateRenderTarget();
}

void Renderer::CreateDevice(Window& window)
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };

	swapChainDesc.BufferCount       = 1;									// 1 additional buffer, meaning 2 buffers overall. e.g double buffering.
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage       = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow      = window.GetHandle();
	swapChainDesc.SampleDesc.Count  = 1;									// Multisampling.
	swapChainDesc.Windowed          = true;


	auto result = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&m_pSwapChain,
		&m_pDevice,
		nullptr,
		&m_pDeviceContext
	);

	if (result != S_OK)
	{
		MessageBoxA(nullptr, "DX11 init boom", "Error", MB_OK);
		exit(0);
	}
}

void Renderer::CreateRenderTarget()
{
	ID3D11Texture2D* buffer;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);

	// If we failed to fetch buffer from swap chain, don't create render target or release the buffer, since nothing's been allocated to it.
	if (buffer != 0)
	{
		m_pDevice->CreateRenderTargetView(buffer, nullptr, &m_pRenderTargetView);

		buffer->GetDesc(&m_backBufferDesc);
		buffer->Release();
	}
}

void Renderer::BeginFrame()
{
	// Render target
	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, nullptr);

	// Viewport
	auto viewport = CD3D11_VIEWPORT(0, 0.f, (float)m_backBufferDesc.Width, (float)m_backBufferDesc.Height);
	m_pDeviceContext->RSSetViewports(1, &viewport);

	// Scene bg color
	float bgColor[] = { .384f, 0.718f, 0.471f, 1 };
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, bgColor);
}

void Renderer::EndFrame()
{
	// Swap buffer
	m_pSwapChain->Present(1, 0);
}

ID3D11Device* Renderer::GetDevice()
{
	return this->m_pDevice;
}

ID3D11DeviceContext* Renderer::GetContext()
{
	return this->m_pDeviceContext;
}