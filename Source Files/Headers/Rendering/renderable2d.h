#pragma once

#include "bindable.h"
#include "graphics.h"
#include "vertexconstants.h"

/*
class Renderable2D
{
public:
	virtual ~Renderable2D() = default;
	virtual void Bind(Graphics& gfx) const = 0;
	virtual void AddBind(std::shared_ptr<Bindable> bind) = 0;
	virtual DirectX::XMMATRIX GetTransform(Graphics& gfx) = 0;
	virtual UINT GetIndexCount() const = 0;
	virtual void Update(Graphics& gfx, float xx, float yy, float dt) = 0;
	virtual VertexData* GetVertexData() const = 0;
	virtual unsigned short* GetIndices() const = 0;
	
protected:
	UINT m_IndexCount;
	VertexConstant* m_VcBuffer;
	std::vector<std::shared_ptr<Bindable>> m_Binds;

};
*/

class Renderable2D
{
public:
	virtual ~Renderable2D() = default;
	virtual void Bind(Graphics& gfx) const = 0;
	virtual void AddBind(std::shared_ptr<Bindable> bind) = 0;
	virtual DirectX::XMMATRIX GetTransform(Graphics& gfx) = 0;
	virtual UINT GetIndexCount() const = 0;
	virtual void Update(Graphics& gfx, float xx, float yy, float dt) = 0;
	virtual VertexData* GetVertexData() const = 0;
	virtual unsigned short* GetIndices() const = 0;
	virtual unsigned int GetVertexCount() const = 0;
	virtual void Cleanup() = 0;

protected:
	UINT m_IndexCount;
	VertexConstant* m_VcBuffer;
	std::vector<std::shared_ptr<Bindable>> m_Binds;

};

