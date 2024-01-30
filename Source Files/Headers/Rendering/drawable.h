#pragma once
#include "../pch.h"
#include "buffer.h"
#include "Headers/Rendering/indexbuffer.h"

class Bindable;

class Drawable
{
public:
	Drawable() = default;
	Drawable(const Drawable& obj) = delete;
	void AddBind(std::unique_ptr<Bindable> bind);
	void AddIndexBuffer(std::unique_ptr<class IndexBuffer> ibuf);
	void Draw(Graphics& gfx);
	virtual ~Drawable() = default;

private:
	std::vector<std::unique_ptr<Bindable>> m_Binds;
	const IndexBuffer* m_Ibuf = nullptr;
};