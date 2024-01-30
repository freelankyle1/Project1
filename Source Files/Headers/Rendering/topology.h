#pragma once
#include "../pch.h"
#include "bindable.h"

class Graphics;

class Topology : public Bindable
{
public:
	Topology(D3D11_PRIMITIVE_TOPOLOGY tp, Graphics& gfx);
	void Bind(Graphics& gfx) const override;
private:
	const D3D11_PRIMITIVE_TOPOLOGY m_tp;
};