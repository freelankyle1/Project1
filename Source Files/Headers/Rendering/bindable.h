#pragma once
#include "../pch.h"
#include "graphics.h"

class Bindable
{
public:
	virtual void Bind(Graphics& gfx) const = 0;
	virtual ~Bindable() = default;
protected:
	static ID3D11Device* GetDevice(const Graphics& gfx);
	static ID3D11DeviceContext* GetContext(const Graphics& gfx);
};