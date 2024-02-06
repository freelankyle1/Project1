#include "Headers/pch.h"
#include "Headers/Rendering/topology.h"

Topology::Topology(Graphics& gfx, D3D11_PRIMITIVE_TOPOLOGY tp)
	:m_tp(tp)
{}

void Topology::Bind(Graphics& gfx)
{
	gfx.GetContext()->IASetPrimitiveTopology(m_tp);
}