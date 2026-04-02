#pragma once
#include "ControllerButton.h"
#include <memory>

namespace dae
{

	class Gamepad final
	{
	public:

		explicit Gamepad(unsigned int controllerIndex);
		~Gamepad();

		void Update();

		bool IsDown(ControllerButton button) const;
		bool IsUp(ControllerButton button) const;
		bool IsPressed(ControllerButton button) const;

	private:
		struct Impl;
		std::unique_ptr<Impl> m_pImpl;
	};
}