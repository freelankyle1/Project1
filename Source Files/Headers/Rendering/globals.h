#pragma once
#include "../pch.h"
#include <DirectXMath.h>

//Microsoft::WRL::ComPtr<ID3DBlob> pBlob;

struct Vertex
{
	struct
	{
		float x;
		float y;
		float z;
	}pos;

};

struct ConstantBuffer
{
	DirectX::XMMATRIX transform;
};

struct ConstantBuffer2
{
	struct
	{
		float r;
		float g;
		float b;
		float a;
	}face_colors[6];
};
