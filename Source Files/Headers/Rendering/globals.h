#pragma once
#include <DirectXMath.h>

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

struct VertexData
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT4 col;
};