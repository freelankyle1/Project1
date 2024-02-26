#include "Headers/pch.h"
#include "Headers/Rendering/renderer2d.h"
#include "Headers/Rendering/vertexconstants.h"
#include "Headers/Rendering/pixelconstants.h"
#include "Headers/Rendering/shader.h"
#include "Headers/Rendering/inputlayout.h"
#include "Headers/Rendering/topology.h"


Renderer2D::Renderer2D(Graphics& gfxDevice)
	: gfx(gfxDevice), vDataSize(0), indexCount(0)
{
	vData = new VertexData[MAX_VERTEX_COUNT];
	memset(vData, 0, MAX_VERTEX_COUNT * sizeof(VertexData));
	iData = new unsigned short[MAX_INDEX_COUNT];
	memset(iData, 0, MAX_INDEX_COUNT * 2);

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
		{"POSITION", 0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
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

	stats.DrawCalls = 0;
	stats.TotalVertices = 0;
}

void Renderer2D::BeginScene()
{
	gfx.ClearBuffer(0.0f, 0.0f, 0.0f);
}

void Renderer2D::Flush()
{
	StartBatch();
	gfx.DrawIndexed(indexCount);

	stats.DrawCalls++;

	vDataSize = 0;
	indexCount = 0;

}

void Renderer2D::Submit(std::shared_ptr<Renderable2D> obj)
{
	if (indexCount >= MAX_INDEX_COUNT)
		Flush();

	VertexData* VertexData = obj->GetVertexData();
	unsigned short* IndexData = obj->GetIndices();

	int VertexCount = obj->GetVertexCount();
	int IndexCount = obj->GetIndexCount();

	for (int i = 0; i < VertexCount; ++i)
	{
		vData[vDataSize + i] = VertexData[i];
	}

	vDataSize += VertexCount;
	stats.TotalVertices += VertexCount;
	
	for (int i = 0; i < IndexCount; ++i)
		iData[indexCount + i] = IndexData[i];
	
	if (indexCount != 0)
	{
		for (int i = 0; i < IndexCount; ++i)
		{
			iData[indexCount + i] = iData[(indexCount + i) - IndexCount] + VertexCount;
		}
	}

	indexCount += IndexCount;

	VertexData = nullptr;
	IndexData = nullptr;
}

void Renderer2D::StartBatch()
{
	VertexBuffer vBuffer(gfx, vData, vDataSize);
	vBuffer.Bind(gfx);

	IndexBuffer iBuffer(gfx, iData, indexCount);
	iBuffer.Bind(gfx);
}

static float translationX = 0.0f;
static float translationY = 0.0f;
static float translationZ = 5.0f;

void Renderer2D::Update(float transX, float transY, float transZ)
{
	translationX += transX;
	translationY += transY;
	translationZ += transZ;

	ConstantBuffer cb = {
		DirectX::XMMatrixTranspose(
			DirectX::XMMatrixTranslation(translationX, translationY, translationZ) * gfx.GetProjection())
	};

	vConst->UpdateConstant(cb);
}

void Renderer2D::EndScene()
{
	gfx.EndFrame();
}


void Renderer2D::Shutdown()
{
	delete[] vData;
	delete[] iData;
}

//debugging purposes
const RendererStats& Renderer2D::GetStats()
{
	return stats;
}

void Renderer2D::EndStats()
{
	stats.DrawCalls = 0;
	stats.TotalVertices = 0;
}

