#include "pch.h"
#include "Triangle.h"
#include <fstream>
#include <vector>

using namespace std;

struct Vertex {
	float x, y;
	float r, g, b;
};

Triangle::Triangle(Renderer& renderer)
{
	CreateMesh(renderer);
	CreateShaders(renderer);
}

Triangle::~Triangle()
{
	m_pVertexBuffer->Release();
	m_pVertexShader->Release();
	m_pPixelShader->Release();
	m_pInputLayout->Release();
}

void Triangle::Draw(Renderer& renderer)
{
	auto ctx = renderer.GetContext();

	// Bind triangle shaders
	ctx->IASetInputLayout(m_pInputLayout);
	ctx->VSSetShader(m_pVertexShader, nullptr, 0);
	ctx->PSSetShader(m_pPixelShader, nullptr, 0);

	// Bind vertex buffer
	//	- We bind it once, then we can render multiple of them if we'd like, so long as it's the same thing, can be of diff position.
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	renderer.GetContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	// Draw
	renderer.GetContext()->Draw(3, 0);
}

void Triangle::CreateMesh(Renderer& renderer)
{
	// Vertices
	Vertex vertices[] = {
		{ -1, -1, 1, 0, 0 },
		{ 0, 1, 0, 1, 0   },
		{ 1, -1, 0, 0, 1  } ,
	};

	auto vertexBufferDesc = CD3D11_BUFFER_DESC(sizeof(vertices), D3D11_BIND_VERTEX_BUFFER);
	D3D11_SUBRESOURCE_DATA vertexData = { 0 };
	vertexData.pSysMem = vertices;

	renderer.GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &m_pVertexBuffer);

}

void Triangle::CreateShaders(Renderer& renderer)
{
	// Shaders
	ifstream vsFile("triangleVertexShader.cso", ios::binary);
	ifstream psFile("trianglePixelShader.cso", ios::binary);

	vector<char> vsData = { istreambuf_iterator<char>(vsFile), istreambuf_iterator<char>() };
	vector<char> psData = { istreambuf_iterator<char>(psFile), istreambuf_iterator<char>() };

	renderer.GetDevice()->CreateVertexShader(vsData.data(), vsData.size(), nullptr, &m_pVertexShader);
	renderer.GetDevice()->CreatePixelShader(psData.data(), psData.size(), nullptr, &m_pPixelShader);

	// Input layouts
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{
			"POSITION",
			0,
			DXGI_FORMAT_R32G32_FLOAT,
			0,
			0,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
		{
			"COLOR",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		}
	};

	renderer.GetDevice()->CreateInputLayout(layout, 2, vsData.data(), vsData.size(), &m_pInputLayout);
}
