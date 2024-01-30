#include "Headers/pch.h"
#include "Headers/Rendering/bindable.h"

ID3D11Device* Bindable::GetDevice(const Graphics& gfx)
{
	return gfx.m_Device.Get();
}

ID3D11DeviceContext* Bindable::GetContext(const Graphics& gfx)
{
	return gfx.m_DevContext.Get();
}