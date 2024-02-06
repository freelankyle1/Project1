#include "Headers/pch.h"
#include "Headers/Rendering/pixelconstants.h"
#include "Headers/asserts.h"

PixelConstant::PixelConstant(Graphics& gfx, ConstantBuffer2& constBuffer)
{
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0u;
	bd.StructureByteStride = 0u;
	bd.ByteWidth = sizeof(constBuffer);

	D3D11_SUBRESOURCE_DATA sr = {};
	sr.pSysMem = &constBuffer;

	HRESULT hr;
	hr = gfx.GetDevice()->CreateBuffer(&bd, &sr, &m_pBuffer);
	ASSERT(hr, "failed to create pixel constant buffer!");

}

void PixelConstant::Bind(Graphics& gfx)
{
	gfx.GetContext()->PSSetConstantBuffers(0u, 1u, m_pBuffer.GetAddressOf());
}
