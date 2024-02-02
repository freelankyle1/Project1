#include "Headers/pch.h"
#include "Headers/Rendering/globals.h"
#include "Headers/Rendering/box.h"
#include "Headers/Rendering/vertexbuffer.h"
#include "Headers/Rendering/indexbuffer.h"
#include "Headers/Rendering/vertexconstants.h"
#include "Headers/Rendering/pixelconstants.h"
#include "Headers/Rendering/shader.h"
#include "Headers/Rendering/inputlayout.h"
#include "Headers/Rendering/topology.h"
#include <random>


Box::Box(Graphics& gfx)
{
	using namespace Microsoft::WRL;

	std::random_device rd;
	std::mt19937 mt(rd());

	std::uniform_int_distribution<int> distribution(1, 45);
	float randomNumber = distribution(mt);

	rotationX = randomNumber;
	rotationZ = randomNumber;

	std::random_device rd2;
	std::mt19937 mt2(rd2());
	std::uniform_real_distribution<float> distribution2(-10.0f, 10.0f);

	randTranslationX = distribution2(mt2);

	using namespace DirectX;

	std::vector<Vertex> vertices =
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

	//VertexBuffer vb(gfx, vertices);


	AddBind(std::make_shared<VertexBuffer>(gfx, vertices));

	//VertexShader vs(L"VertexShader.cso", gfx);
	
	auto pvs = std::make_shared<VertexShader>(gfx, L"VertexShader.cso");
	auto pvsbc = pvs->GetByteCode();
	AddBind(std::move(pvs));
	
	//PixelShader ps(L"PixelShader.cso", gfx);
	AddBind(std::make_shared<PixelShader>(gfx, L"PixelShader.cso"));

	std::vector<USHORT> indices =
	{
		0,2,1, 2,3,1,
		1,3,5, 3,7,5,
		2,6,3, 3,6,7,
		4,5,7, 4,7,6,
		0,4,2, 2,4,6,
		0,1,4, 1,5,4
	};

	//IndexBuffer ib(gfx, indices);
	AddIndexBuffer(std::make_shared<IndexBuffer>(gfx, indices));

	ConstantBuffer2 cb2
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

	//PixelConstant pcbuffer(gfx, cb2);
	AddBind(std::make_shared<PixelConstant>(gfx, cb2));

	std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
	{
		{"Position", 0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0}
	};

	//InputLayout il(gfx, ied, pvsbc);
	AddBind(std::make_shared<InputLayout>(gfx, ied, pvsbc));

	//Topology tp(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	AddBind(std::make_shared<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	m_cb.transform *= gfx.GetProjection();

	std::shared_ptr vcb = std::make_shared<VertexConstant>(gfx, m_cb);
	vcbuffer = vcb.get();
	AddBind(std::move(vcb));
}

void Box::AddBind(std::shared_ptr<Bindable> bind)
{
	Binds.push_back(std::move(bind));
}


void Box::AddIndexBuffer(std::shared_ptr<IndexBuffer> ib)
{
	m_IndexCount = ib->GetSize();
	Binds.push_back(std::move(ib));
}

void Box::Draw(Graphics& gfx)
{
	for (const auto& it : Binds)
	{
		it->Bind(gfx);
	}
	gfx.DrawIndexed(m_IndexCount);
}

DirectX::XMMATRIX Box::GetTransform(Graphics& gfx)
{
	using namespace DirectX;
	return	XMMatrixRotationZ(0) *
			XMMatrixRotationX(rotationX) *
			XMMatrixTranslation(randTranslationX, 0.0f, 15.0f);
}

void Box::Update(Graphics& gfx, float dt)
{
	using namespace DirectX;

	//rotationZ += 0.05f / 4;
	rotationX += 0.025f / 2;

	ConstantBuffer cb = {
		XMMatrixTranspose(
		GetTransform(gfx) * gfx.GetProjection())
	};


	vcbuffer->UpdateConstant(gfx, cb );
}

