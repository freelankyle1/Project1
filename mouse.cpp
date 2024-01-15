#include "pch.h"
#include "Headers/Mouse.h"


std::pair<int, int> kMouse::GetPos() const noexcept
{
	return { x, y };
}

int kMouse::GetPosX() const noexcept
{
	return x;
}

int kMouse::GetPosY() const noexcept
{
	return y;
}

bool kMouse::LeftIsPressed() const noexcept
{
	return leftIsPressed;
}

bool kMouse::RightIsPressed() const noexcept
{
	return rightIsPressed;
}

kMouse::Event kMouse::Read() noexcept
{
	if (buffer.size() > 0u)
	{
		kMouse::Event e = buffer.front();
		buffer.pop();
		return e;
	}
	else
	{
		return kMouse::Event();
	}
}

void kMouse::Flush() noexcept
{
	buffer = std::queue<Event>();
}

bool kMouse::IsInWindow() const noexcept
{
	return isInWindow;
}

void kMouse::OnMouseMove(int newx, int newy) noexcept
{
	x = newx;
	y = newy;

	buffer.push(kMouse::Event(kMouse::Event::Type::Move, *this));
	TrimBuffer();
}

void kMouse::OnMouseLeave() noexcept
{
	isInWindow = false;
	buffer.push(kMouse::Event(kMouse::Event::Type::Leave, *this));
	TrimBuffer();
}

void kMouse::OnMouseEnter() noexcept
{
	isInWindow = true;
	buffer.push(kMouse::Event(kMouse::Event::Type::Enter, *this));
	TrimBuffer();
}

void kMouse::OnLeftPressed(int x, int y) noexcept
{
	leftIsPressed = true;

	buffer.push(kMouse::Event(kMouse::Event::Type::LPress, *this));
	TrimBuffer();
}

void kMouse::OnLeftReleased(int x, int y) noexcept
{
	leftIsPressed = false;

	buffer.push(kMouse::Event(kMouse::Event::Type::LRelease, *this));
	TrimBuffer();
}

void kMouse::OnRightPressed(int x, int y) noexcept
{
	rightIsPressed = true;

	buffer.push(kMouse::Event(kMouse::Event::Type::RPress, *this));
	TrimBuffer();
}
void kMouse::OnRightReleased(int x, int y) noexcept
{
	rightIsPressed = false;

	buffer.push(kMouse::Event(kMouse::Event::Type::RRelease, *this));
	TrimBuffer();
}

void kMouse::OnWheelUp(int x, int y) noexcept
{
	buffer.push(kMouse::Event(kMouse::Event::Type::WheelUp, *this));
	TrimBuffer();
}

void kMouse::OnWheelDown(int x, int y) noexcept
{
	buffer.push(kMouse::Event(kMouse::Event::Type::WheelDown, *this));
	TrimBuffer();
}

void kMouse::TrimBuffer() noexcept
{
	while (buffer.size() > bufferSize)
	{
		buffer.pop();
	}
}