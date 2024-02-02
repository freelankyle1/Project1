#pragma once
#include "../pch.h"
#include "graphics.h"
#include "bindable.h"


class Topology : public Bindable
{
public:
	Topology(Graphics& gfx, D3D11_PRIMITIVE_TOPOLOGY tp);
	void Bind(Graphics& gfx) override;
private:
	const D3D11_PRIMITIVE_TOPOLOGY m_tp;
};