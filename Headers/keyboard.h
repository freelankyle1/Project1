#pragma once
#include "../pch.h"

#include <queue>
#include <bitset>


class Keyboard
{
	friend class window;

public:
	class Event
	{
	public:
		enum class Type
		{
			press,
			release,
			invalid
		};
	private:
		Type type;
		unsigned char code;
	public:
		Event()
			: type (Type::invalid), code (0u)
		{}
		Event(Type type, unsigned char code) noexcept
			: type(type), code(code)
		{}
		bool IsPress() const noexcept
		{
			return type == Type::press;
		}
		bool IsRelease() const noexcept
		{
			return type == Type::release;
		}
		bool IsValid() const noexcept
		{
			return type != Type::invalid;
		}
		unsigned char GetCode() const noexcept
		{
			return code;
		}
	};


	Keyboard() = default;
	Keyboard(const Keyboard&) = delete;
	Keyboard& operator=(const Keyboard&) = delete;

	bool KeyIsPressed(unsigned char keycode) const noexcept;
	Event ReadKey() noexcept;
	bool KeyIsEmpty() const noexcept;
	void FlushKey() noexcept;

	char ReadChar() noexcept;
	bool CharIsEmpty() const noexcept;
	void FlushChar() noexcept;
	void Flush() noexcept;

	void EnableAutorepeat() noexcept;
	void DisableAutorepeat() noexcept;
	bool AutorepeatIsEnabled() const noexcept;

private:
	void OnKeyPressed(unsigned char keycode) noexcept;
	void OnKeyReleased(unsigned char keycode) noexcept;
	void OnChar(char character) noexcept;
	void ClearState() noexcept;
	template <typename T>
	static void TrimBuffer(std::queue<T>& buffer) noexcept;
private:
	static constexpr unsigned int nKeys = 256u;
	static constexpr unsigned int bufferSize = 16u;
	bool autorepeastEnabled = false;
	std::bitset<nKeys> keystates;
	std::queue<Event> keybuffer;
	std::queue<char> charbuffer;

};