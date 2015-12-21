#pragma once

#include "BaseScreen.h"

class MainMenuScreen : public BaseScreen
{
public:
	MainMenuScreen(ScreenManager* screenManager, const std::string& dataAsset);
	~MainMenuScreen();

	void AddInitialUI() override;
};

