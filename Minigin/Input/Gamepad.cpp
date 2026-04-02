#include "Gamepad.h"

#ifndef __EMSCRIPTEN__
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Xinput.h>
#pragma comment(lib, "xinput.lib")
#endif // !__EMSCRIPTEN__



namespace dae
{
	struct Gamepad::Impl
	{
#ifndef __EMSCRIPTEN__
		unsigned int index{};
		XINPUT_STATE previousState{};
		XINPUT_STATE currentState{};

		WORD buttonsPressedThisFrame{};
		WORD buttonsReleasedThisFrame{};
#endif // !__EMSCRIPTEN__
	};

	Gamepad::Gamepad(unsigned int controllerIndex)
		: m_pImpl(std::make_unique<Impl>())
	{
#ifndef __EMSCRIPTEN__
		m_pImpl->index = controllerIndex;
		ZeroMemory(&m_pImpl->previousState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_pImpl->currentState, sizeof(XINPUT_STATE));
#else
		(void)controllerIndex;
#endif // !__EMSCRIPTEN__
	}

	Gamepad::~Gamepad() = default;

	void Gamepad::Update()
	{
#ifndef __EMSCRIPTEN__
		CopyMemory(&m_pImpl->previousState, &m_pImpl->currentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_pImpl->currentState, sizeof(XINPUT_STATE));
		XInputGetState(m_pImpl->index, &m_pImpl->currentState);

		auto buttonChanges = m_pImpl->currentState.Gamepad.wButtons ^ m_pImpl->previousState.Gamepad.wButtons;

		m_pImpl->buttonsPressedThisFrame = buttonChanges & m_pImpl->currentState.Gamepad.wButtons;
		m_pImpl->buttonsReleasedThisFrame = buttonChanges & (~m_pImpl->currentState.Gamepad.wButtons);
#endif // !__EMSCRIPTEN__
	}

	bool Gamepad::IsDown(ControllerButton button) const
	{
#ifndef __EMSCRIPTEN__
		return m_pImpl->buttonsPressedThisFrame & static_cast<unsigned>(button);
#else
		(void)button;
		return false;
#endif // !__EMSCRIPTEN__

	}

	bool Gamepad::IsUp(ControllerButton button) const
	{
#ifndef __EMSCRIPTEN__
		return m_pImpl->buttonsReleasedThisFrame & static_cast<unsigned>(button);
#else
		(void)button;
		return false;
#endif // !__EMSCRIPTEN__
	}

	bool Gamepad::IsPressed(ControllerButton button) const
	{
#ifndef __EMSCRIPTEN__
		return m_pImpl->currentState.Gamepad.wButtons & static_cast<unsigned>(button);
#else
		(void)button;
		return false;
#endif // !__EMSCRIPTEN__
	}
}






