#pragma once

#include "StepTimer.h"

using namespace DirectX;

class KeyboardInput
{
public:
	KeyboardInput();
	~KeyboardInput();

	void Update(DX::StepTimer const& timer);

	/// \brief Utility functions for input
	bool IsKeyDown(Keyboard::Keys key);
	bool IsKeyPressed(Keyboard::Keys key);

private:
	std::unique_ptr<Keyboard> m_keyboard;

	// Hold all the information for the keyboard state - can be found in Keyboard.h
	Keyboard::State m_previousKeyboardState;
	Keyboard::State m_currentKeyboardState;
};

