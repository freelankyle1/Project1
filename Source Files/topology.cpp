#include "Headers/pch.h"
#include "Headers/Rendering/topology.h"

Topology::Topology(D3D11_PRIMITIVE_TOPOLOGY tp, Graphics& gfx)
	:m_tp(tp)
{
	Bind(gfx);
}

void Topology::Bind(Graphics& gfx) const
{
	GetContext(gfx)->IASetPrimitiveTopology(m_tp);
}