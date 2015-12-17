#include "pch.h"
#include "Script.h"


//-----------------------------------------------------------------------------------------------------------------------------------
Script::Script(const bool shouldUpdateGame, const bool canRun) :
	m_canRun(canRun),
	m_shouldUpdateGame(shouldUpdateGame),
	m_running(false),
	m_completed(false),
	m_timeRunFor(0),
	m_previousScript(nullptr)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
Script::~Script()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Script::SetCanRunOnScriptCompleted(const Script* previousScript)
{
	m_canRunFunction = [](const Script* previousScript)
	{
		return previousScript->IsCompleted();
	};
}


//-----------------------------------------------------------------------------------------------------------------------------------
const bool Script::CanRun()
{
	if (IsRunning())
	{
		return true;
	}

	if (m_canRunFunction)
	{
		assert(m_previousScript);
		return m_canRunFunction(m_previousScript);
	}

	return m_canRun;
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Script::Run(DX::StepTimer const& timer)
{
	m_running = true;
	m_timeRunFor += static_cast<float>(timer.GetElapsedSeconds());
}