#include "Headers/pch.h"
#include "Headers/Rendering/drawable.h"


void Drawable::AddBind(std::unique_ptr<Bindable> bind)
{
	m_Binds.emplace_back(std::move(bind));
}

void Drawable::AddIndexBuffer(std::unique_ptr<IndexBuffer> ibuf)
{
	m_Ibuf = ibuf.get();
	m_Binds.emplace_back(std::move(ibuf));
}

void Drawable::Draw(Graphics& gfx)
{
	for (const auto& it : m_Binds)
	{
		it->Bind(gfx);
	}
	gfx.DrawIndexed(m_Ibuf->GetSize());
}