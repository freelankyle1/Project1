#pragma once
#include "../pch.h"
#include "vertexconstants.h"
#include "bindable.h"

class Graphics;


class Box
{
public:
	Box(Graphics& gfx);
	void Draw(Graphics& gfx);
	void Update(Graphics& gfx, float dt);
	DirectX::XMMATRIX GetTransform(Graphics& gfx);

private:
	void AddBind(std::shared_ptr<Bindable> bind);
	void AddIndexBuffer(std::shared_ptr<class IndexBuffer> ib);

private:
	float rotationX;
	float rotationZ;
	float randTranslationX;

	static UINT m_IndexCount;
	static bool StaticInit;

	//VertexConstant* vertexRef;
	ConstantBuffer m_cb = {
		DirectX::XMMatrixRotationZ(0.0f)*
		DirectX::XMMatrixRotationX(0.0f)*
		DirectX::XMMatrixRotationY(0.0f)*
		DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f)
	};
	VertexConstant* vcbuffer;

	std::vector<std::shared_ptr<Bindable>> Binds;

};

