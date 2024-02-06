#pragma once

#include "bindable.h"
#include "graphics.h"

class Renderable2D
{
public:
	virtual ~Renderable2D() = default;
	virtual void Bind(Graphics& gfx) const = 0;
	virtual void AddBind(std::shared_ptr<Bindable> bind) = 0;
	virtual DirectX::XMMATRIX GetTransform(Graphics& gfx) = 0;
	virtual UINT GetIndexCount() const = 0;
	virtual void Update(Graphics& gfx, float dt) = 0;
	

protected:
	UINT m_IndexCount;
	VertexConstant* m_VcBuffer;
	std::vector<std::shared_ptr<Bindable>> m_Binds;

};