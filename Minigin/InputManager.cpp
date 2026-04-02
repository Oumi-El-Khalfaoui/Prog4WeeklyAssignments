#include <SDL3/SDL.h>
#include "InputManager.h"
#include "Input/Gamepad.h"
#include "Input/ControllerButton.h"


namespace dae
{
	InputManager::~InputManager() = default;

	Gamepad* dae::InputManager::GetOrCreateGamepad(unsigned int index)
	{
		auto it = m_gamepads.find(index);
		if (it == m_gamepads.end())
		{
			m_gamepads[index] = std::make_unique<Gamepad>(index);
			it = m_gamepads.find(index);
		}

		return it->second.get();
	}

}



bool dae::InputManager::ProcessInput()
{
	int numKeys{};
	m_keyboardState = SDL_GetKeyboardState(&numKeys);

	if (static_cast<int>(m_prevKeyboardState.size()) != numKeys)
	{
		m_prevKeyboardState.assign(numKeys, false);
	}

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_EVENT_QUIT) {
			return false;
		}
		
	}

	for (auto& binding : m_keyboardBindings)
	{
		const bool curr = m_keyboardState[binding.key];
		const bool prev = m_prevKeyboardState[binding.key];

		bool fire = false;
		switch (binding.state)
		{
		case KeyState::Down:
			fire = curr && !prev;
			break;
		case KeyState::Up:
			fire = !curr && prev;
			break;
		case KeyState::Pressed:
			fire = curr;
			break;
		}

		if (fire)
		{
			binding.command->Execute();
		}
	}

	for (int i = 0; i < numKeys; ++i)
	{
		m_prevKeyboardState[i] = m_keyboardState[i];
	}

#ifndef __EMSCRIPTEN__
	for (auto& [idx, pad] : m_gamepads) 
	{
		pad->Update();
	}

	for (auto& binding : m_controllerBindings)
	{
		Gamepad* pad = GetOrCreateGamepad(binding.controllerIndex);

		bool fire = false;

		switch (binding.state)
		{
		case KeyState::Down:
			fire = pad->IsDown(binding.button);
			break;
		case KeyState::Up:
			fire = pad->IsUp(binding.button);
			break;
		case KeyState::Pressed:
			fire = pad->IsPressed(binding.button);
			break;
		}

		if (fire)
		{
			binding.command->Execute();
		}
	}

#endif // !__EMSCRIPTEN__
	
	return true;
}

void dae::InputManager::BindKeyboardCommand(SDL_Scancode key, KeyState state, std::unique_ptr<Command> command)
{
	m_keyboardBindings.push_back({ key, state, std::move(command) });
}

void dae::InputManager::UnbindKeyboardCommand(SDL_Scancode key, KeyState state)
{
	m_keyboardBindings.erase(std::remove_if(m_keyboardBindings.begin(), m_keyboardBindings.end(), [&](const KeyboardBinding& b) {return b.key == key && b.state == state; }), m_keyboardBindings.end());
}

void dae::InputManager::BindControllerCommand(unsigned int controllerIndex, ControllerButton button, KeyState state, std::unique_ptr<Command> command)
{
	GetOrCreateGamepad(controllerIndex);
	m_controllerBindings.push_back({ controllerIndex, button, state, std::move(command) });
}

void dae::InputManager::UnbindControllerCommand(unsigned int controllerIndex, ControllerButton button, KeyState state)
{
	m_controllerBindings.erase(std::remove_if(m_controllerBindings.begin(), m_controllerBindings.end(), [&](const ControllerBinding& b) { return b.controllerIndex == controllerIndex && b.button == button && b.state == state; }), m_controllerBindings.end());
}

