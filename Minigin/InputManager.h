#pragma once
#include "Singleton.h"
#include "Input/Command.h"
#include "Input/Gamepad.h"
#include "Input/ControllerButton.h"

#include <SDL3/SDL.h>
#include <memory>
#include <vector>
#include <map>

namespace dae
{
	enum class KeyState 
	{
		Down, 
		Up, 
		Pressed
	};

	class Gamepad;

	class InputManager final : public Singleton<InputManager>
	{
	public:
		~InputManager();

		bool ProcessInput();

		void BindKeyboardCommand(SDL_Scancode key, KeyState state, std::unique_ptr<Command> command);
		void UnbindKeyboardCommand(SDL_Scancode key, KeyState state);

		void BindControllerCommand(unsigned int controllerIndex, ControllerButton button, KeyState state, std::unique_ptr<Command> command);
		void UnbindControllerCommand(unsigned int controllerIndex, ControllerButton button, KeyState state);

	private:
		struct KeyboardBinding
		{
			SDL_Scancode key;
			KeyState state;
			std::unique_ptr<Command> command;
		};

		std::vector<KeyboardBinding> m_keyboardBindings;

		const bool* m_keyboardState{ nullptr };
		std::vector<bool> m_prevKeyboardState;

		struct ControllerBinding
		{
			unsigned int controllerIndex;
			ControllerButton button;
			KeyState state;
			std::unique_ptr<Command> command;
		};
		std::vector<ControllerBinding> m_controllerBindings;
		std::map<unsigned int, std::unique_ptr<Gamepad>> m_gamepads;

		Gamepad* GetOrCreateGamepad(unsigned int index);
	};

}
