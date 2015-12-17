#pragma once

#include "Script.h"

#include <list>

class BaseScreen;

class ScriptManager
{
public:
	ScriptManager(BaseScreen* baseScreen);
	~ScriptManager();

private:
	/// brief Typedefs
	typedef std::list<std::unique_ptr<Script>> Scripts;

	Scripts m_activeScripts;
	Scripts m_scriptsToDelete;

	BaseScreen* m_baseScreen;
};