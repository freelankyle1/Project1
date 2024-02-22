#include "Headers/pch.h"
#include "Headers/Rendering/renderer2d.h"
#include "Headers/Rendering/vertexconstants.h"
#include "Headers/Rendering/pixelconstants.h"
#include "Headers/Rendering/shader.h"
#include "Headers/Rendering/inputlayout.h"
#include "Headers/Rendering/topology.h"

Renderer2D::Renderer2D(Graphics& gfxDevice)
	: gfx(gfxDevice)
{
	vData = new VertexData[MAX_VERTEX_BYTE_COUNT];
	memset(vData, 0, MAX_INDEX_BYTE_COUNT);
	iData = new unsigned short[MAX_INDEX_BYTE_COUNT];
	memset(iData, 0, MAX_INDEX_BYTE_COUNT);

	VertexShader vs(gfx, L"VertexShader.cso");
	auto pvsbc = vs.GetByteCode();
	vs.Bind(gfxDevice);

	PixelShader ps(gfx, L"PixelShader.cso");
	ps.Bind(gfxDevice);

	ConstantBuffer2 cb2
	{
		{
			{0.5f,0.5f,1.0f},
		}
	};

	PixelConstant pc(gfx, cb2);
	pc.Bind(gfxDevice);

	std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
	{
		{"Position", 0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0}
	};

	InputLayout il(gfx, ied, pvsbc);
	il.Bind(gfxDevice);

	Topology tp(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	tp.Bind(gfxDevice);

	ConstantBuffer cb;
	cb.transform =  DirectX::XMMatrixRotationZ	(0.0f) *
					DirectX::XMMatrixRotationY	(0.0f) *
					DirectX::XMMatrixRotationX	(0.0f) *
					DirectX::XMMatrixTranslation(0.0f, 0.0f, 5.0f);
	cb.transform = cb.transform * gfx.GetProjection();

	vConst = std::make_unique<VertexConstant>(gfx);
	vConst->Initialize(cb);
	vConst->Bind(gfx);
}

void Renderer2D::Flush()
{
	VertexBuffer vBuffer(gfx, vData, vDataSize);
	vBuffer.Bind(gfx);

	IndexBuffer iBuffer(gfx, iData, indexCount);
	iBuffer.Bind(gfx);
	
	gfx.DrawIndexed(indexCount);

	vDataSize = 0;
	indexCount = 0;

	delete[] vData;
	delete[] iData;

	vData = new VertexData[MAX_VERTEX_BYTE_COUNT];
	memset(vData, 0, MAX_INDEX_BYTE_COUNT);
	iData = new unsigned short[MAX_INDEX_BYTE_COUNT];
	memset(iData, 0, MAX_INDEX_BYTE_COUNT);

}

void Renderer2D::Submit(std::shared_ptr<Renderable2D> obj)
{
	VertexData* VertexData = obj->GetVertexData();
	unsigned short* IndexData = obj->GetIndices();

	vData[vDataSize + 0] = VertexData[0];
	vData[vDataSize + 1] = VertexData[1];
	vData[vDataSize + 2] = VertexData[2];
	
	vDataSize += 3;

	iData[indexCount + 0] = IndexData[0];
	iData[indexCount + 1] = IndexData[1];
	iData[indexCount + 2] = IndexData[2];
	
	if (indexCount != 0)
	{
		iData[indexCount + 0] = iData[(indexCount + 0) - 3] + 3;
		iData[indexCount + 1] = iData[(indexCount + 1) - 3] + 3;
		iData[indexCount + 2] = iData[(indexCount + 2) - 3] + 3;
	}

	indexCount += 3;

	VertexData = nullptr;
	IndexData = nullptr;
}

static float translationX = 0.0f;
static float translationZ = 5.0f;

void Renderer2D::Update(float transX, float transY, float transZ)
{
	translationX += transX;
	translationZ += transZ;

	ConstantBuffer cb = {
		DirectX::XMMatrixTranspose(
			DirectX::XMMatrixTranslation(translationX, 0.0f, translationZ) * gfx.GetProjection())
	};

	vConst->UpdateConstant(cb);
}

//debugging purposes
int Renderer2D::GetVertexAmount() const
{
	return vDataSize;
}

void Renderer2D::Shutdown()
{
	delete[] vData;
	delete[] iData;
}


