#pragma once

#include "StepTimer.h"

class Script
{
public:
	Script(const bool shouldUpdateGame, const bool canRun);
	~Script();

public:
	/// \brief Sets this script to run when the inputted script is done 
	void SetCanRunOnScriptCompleted(const Script* previousScript);

	/// \brief Loads and Initializes
	virtual void LoadAndInit(ID3D11Device* device) = 0;

	/// \brief Runs the script
	virtual void Run(DX::StepTimer const& timer);

	/// \brief Draws any in game objects (camera dependent)
	virtual void DrawInGameObjects(SpriteBatch* spriteBatch, SpriteFont* spriteFont) { }

	/// \brief Draws any screen UI (camera independent)
	virtual void DrawScreenObjects(SpriteBatch* spriteBatch, SpriteFont* spriteFont) { }

	/// \brief Returns whether the script can run
	virtual const bool CanRun();

	/// \brief Returns whether the script should update the game
	const bool ShouldUpdateGame() const { return m_shouldUpdateGame; }

	/// \brief Returns whether the script is running
	const bool IsRunning() const { return m_running; }

	/// \brief Returns whether this script has completed
	const bool IsCompleted() const { return m_completed; }

protected:
	/// \brief Sets whether this script can run
	void SetCanRun(const bool canRun) { m_canRun = canRun; }

	/// \brief Sets whether this script should update the game
	void SetShouldUpdateGame(const bool shouldUpdateGame) { m_shouldUpdateGame = shouldUpdateGame; }

	/// \brief Sets whether this script is running
	void SetRunning(const bool running) { m_running = running; }

	/// \brief Sets whether this script has finished running
	void SetCompleted(const bool completed) { m_completed = completed; }

	/// \brief Gets the total time this script has run for
	const float GetTimeRunFor() const { return m_timeRunFor; }

private:
	// Determines whether this script can run
	bool m_canRun;

	// Determines whether this script will also run the main game loop
	bool m_shouldUpdateGame;

	// Determines whether this script is running
	bool m_running;

	// Determines whether this script has finished running
	bool m_completed;

	// The total time the script has run for
	float m_timeRunFor;

	// A custom function for specifying when a script should run
	std::function<bool(const Script* script)> m_canRunFunction;
	Script* m_previousScript;
};

