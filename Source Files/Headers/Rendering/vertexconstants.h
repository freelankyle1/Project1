#pragma once
#include "graphics.h"
#include "globals.h"
#include "bindable.h"

class VertexConstant : public Bindable
{
public:
	VertexConstant(Graphics& gfx);
	VertexConstant(Graphics& gfx, ConstantBuffer& constBuffer);
	void Bind(Graphics& gfx) override;
	void Initialize(ConstantBuffer& constBuffer);
	void UpdateConstant(ConstantBuffer& cb);

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_pBuffer;
	Graphics& gfx;
};