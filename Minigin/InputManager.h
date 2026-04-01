#pragma once
#include "Singleton.h"
#include "Input/Command.h"
#include "Input/Gamepad.h"

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

	enum class ControllerButton : unsigned
	{
		DPadUp = 0x0001,
		DPadDown = 0x0002,
		DPadLeft = 0x0004,
		DPadRight = 0x0008,
		Start = 0x0010,
		Back = 0x0020,
		A = 0x1000,
		B = 0x2000,
		X = 0x4000,
		Y = 0x8000
	};

	class Gamepad;

	class InputManager final : public Singleton<InputManager>
	{
	public:
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
