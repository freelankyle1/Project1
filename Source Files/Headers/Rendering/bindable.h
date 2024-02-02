#pragma once
#include "../pch.h"

class Graphics;

class Bindable
{
public:
	virtual void Bind(Graphics& gfx) = 0;
	virtual ~Bindable() = default;
private:

};