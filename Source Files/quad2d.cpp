#include "Headers/pch.h"

#include "Headers/Rendering/quad2d.h"


Quad2D::Quad2D(Graphics& gfxDevice, float translation)
{
	translationX = translation;

	//vConstant = new VertexConstant(gfxDevice, CBuf);
	//vConstant->Bind(gfxDevice);

	PerVertex = new VertexData[4];
	PerVertex[0] = { DirectX::XMFLOAT3(-1.0f,-1.0f, 0.0f) };
	PerVertex[1] = { DirectX::XMFLOAT3( 1.0f, 1.0f, 0.0f) };
	PerVertex[2] = { DirectX::XMFLOAT3( 1.0f,-1.0f, 0.0f) };
	PerVertex[3] = { DirectX::XMFLOAT3(-1.0f, 1.0f, 0.0f) };
	
	indices = new unsigned short[6];
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 0;
	indices[4] = 3;
	indices[5] = 1;
	
}

Quad2D::~Quad2D()
{
	delete[] PerVertex;
	delete[] indices;
	delete vConstant;
}

DirectX::XMMATRIX Quad2D::GetTransform(Graphics& gfx) 
{
	//send transformations into here

	return  DirectX::XMMatrixRotationZ(0.0f) *
			DirectX::XMMatrixRotationX(0.0f) *
			DirectX::XMMatrixRotationY(0.0f) *
			DirectX::XMMatrixTranslation(translationX, 0.0f, 0.0f);
}

int Quad2D::GetVertexCount() const
{
	return 4;
}

unsigned short* Quad2D::GetIndices() const
{
	return indices;
}
VertexData* Quad2D::GetVertices() const
{
	return PerVertex;
}

void Quad2D::Update(Graphics& gfxDevice) 
{
	ConstantBuffer cb = {
		DirectX::XMMatrixTranspose(
		GetTransform(gfxDevice) * gfxDevice.GetProjection())
	};

	translationX += 0.05f;


	//vConstant->UpdateConstant(gfxDevice, cb);
}
