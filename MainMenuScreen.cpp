#include "pch.h"

#include "MainMenuScreen.h"
#include "GameplayScreen.h"

#include "Button.h"


//-----------------------------------------------------------------------------------------------------------------------------------
MainMenuScreen::MainMenuScreen(ScreenManager* screenManager, const std::string& dataAsset) :
	BaseScreen(screenManager, dataAsset)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
MainMenuScreen::~MainMenuScreen()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void MainMenuScreen::AddInitialUI()
{
	BaseScreen::AddInitialUI();

	Button* playButton = new Button(GetScreenCentre(), L"Play");
	playButton->SetClickFunction([this]()
	{
		// Transition to game screen
		Transition(new GameplayScreen(GetScreenManager(), "Level1Screen.xml"));
	});

	AddScreenUIObject(playButton);
}