#pragma once

#include <DirectXMath.h>

class Graphics;
class VertexConstant;
struct VertexData;

class Renderable
{
public:

	virtual ~Renderable() = default;
	virtual void Update(Graphics& gfxDevice) = 0;
	virtual DirectX::XMMATRIX GetTransform(Graphics& gfx) = 0;
	virtual int GetVertexCount() const = 0;
	virtual unsigned short* GetIndices() const = 0;
	virtual VertexData* GetVertices() const = 0;


	VertexConstant* vConstant;
};
