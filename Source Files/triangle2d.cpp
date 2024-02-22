#include "Headers/pch.h"
#include "Headers/Rendering/globals.h"
#include "Headers/Rendering/triangle2d.h"

bool Triangle2D::staticInit;
UINT Triangle2D::indexCount;

Triangle2D::Triangle2D(Graphics& gfx, const VertexData* vData)
	:translationX(0.0f), translationY(0.0f), translationZ(0.0f), VertexCount(3)
{
	PerVertex = new VertexData[3];

	PerVertex[0].pos = vData[0].pos;
	PerVertex[1].pos = vData[1].pos;
	PerVertex[2].pos = vData[2].pos;

	indices = new unsigned short[3];

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;

}

Triangle2D::~Triangle2D()
{
	delete[] PerVertex;
	delete[] indices;
}

void Triangle2D::Cleanup()
{

}

void Triangle2D::Bind(Graphics& gfx) const
{
	//loop through our vector of binds and bind everything necessary
	//to draw the primitive
	for(const auto & it : m_Binds)
	{
		it->Bind(gfx);
	}
}

void Triangle2D::AddBind(std::shared_ptr<Bindable> bind)
{
	m_Binds.push_back(std::move(bind));
}

void Triangle2D::AddIndexBuffer(std::shared_ptr<IndexBuffer> ib)
{
	indexCount = ib->GetSize();
	m_Binds.push_back(std::move(ib));
}

DirectX::XMMATRIX Triangle2D::GetTransform(Graphics& gfx)
{
	using namespace DirectX;
	return	XMMatrixRotationZ  (0.0f) *
			XMMatrixRotationY  (0.0f) *
			XMMatrixRotationX  (0.0f) *
			XMMatrixTranslation(translationX, 0.0f, 5.0f);
}

UINT Triangle2D::GetIndexCount() const
{
	return indexCount;
}

VertexData* Triangle2D::GetVertexData() const
{
	return PerVertex;
}

unsigned short* Triangle2D::GetIndices() const
{
	return indices;
}

unsigned int Triangle2D::GetVertexCount() const
{
	return VertexCount;
}

//these floats are if we want to move the object based on something
//i.e. camera movement potentially
void Triangle2D::Update(Graphics& gfx, float xx, float zz, float rY)
{
	using namespace DirectX;

	translationX += xx;

	ConstantBuffer cb = {
		XMMatrixTranspose(
		GetTransform(gfx) * gfx.GetProjection())
	};


	m_VcBuffer->UpdateConstant(cb);
}
