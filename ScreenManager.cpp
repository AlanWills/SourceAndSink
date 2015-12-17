#include "pch.h"
#include "ScreenManager.h"

static Vector2 m_screenCentre;
static Camera m_camera;
static GameMouse m_gameMouse;
static KeyboardInput m_keyboard;


//-----------------------------------------------------------------------------------------------------------------------------------
const Vector2& ScreenManager::GetScreenCentre()
{
	return m_screenCentre;
}


//-----------------------------------------------------------------------------------------------------------------------------------
Camera& ScreenManager::GetCamera()
{
	return m_camera;
}


//-----------------------------------------------------------------------------------------------------------------------------------
GameMouse& ScreenManager::GetGameMouse()
{
	return m_gameMouse;
}


//-----------------------------------------------------------------------------------------------------------------------------------
KeyboardInput& ScreenManager::GetKeyboardInput()
{
	return m_keyboard;
}


//-----------------------------------------------------------------------------------------------------------------------------------
ScreenManager::ScreenManager(ID3D11Device* device, ID3D11DeviceContext* deviceContext, float screenWidth, float screenHeight) :
m_device(device),
m_deviceContext(deviceContext),
m_spriteBatch(new SpriteBatch(deviceContext)),
m_spriteFont(new SpriteFont(device, L"Font.spritefont")),
m_states(new CommonStates(device))
{
	m_screenCentre = Vector2(screenWidth, screenHeight) * 0.5f;
}


//-----------------------------------------------------------------------------------------------------------------------------------
ScreenManager::~ScreenManager()
{
	// Need to delete all the screens here
	for (BaseScreen* screen : m_activeScreens)
	{
		delete screen;
	}

	m_activeScreens.clear();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void ScreenManager::LoadContent()
{
	m_gameMouse.LoadContent(m_device);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void ScreenManager::Initialize()
{
	m_gameMouse.Initialize();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void ScreenManager::Update(DX::StepTimer const& timer)
{
	m_keyboard.Update(timer);
	m_camera.Update(timer);
	m_gameMouse.Update(timer);

	for (BaseScreen* screen : m_activeScreens)
	{
		// Screen updating
		screen->Update(timer);
	}

	for (BaseScreen* screen : m_screensToDelete)
	{
		// Clean up dead screens
		m_activeScreens.remove(screen);
		delete screen;
	}

	m_screensToDelete.clear();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void ScreenManager::Draw()
{
	// Draw the background
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states->NonPremultiplied());

	m_activeScreens.back()->DrawBackground(m_spriteBatch.get(), m_spriteFont.get());

	m_spriteBatch->End();

	// Draw the camera dependent game objects
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states->NonPremultiplied(), nullptr, nullptr, nullptr, nullptr, m_camera.GetViewMatrix());

	for (BaseScreen* screen : m_activeScreens)
	{
		screen->DrawInGameObjects(m_spriteBatch.get(), m_spriteFont.get());
	}

	m_spriteBatch->End();

	// Draw the screen (camera independent) objects
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states->NonPremultiplied());

	for (BaseScreen* screen : m_activeScreens)
	{
		screen->DrawScreenObjects(m_spriteBatch.get(), m_spriteFont.get());
	}

	// Draw the game mouse - camera independent
	m_gameMouse.Draw(m_spriteBatch.get(), m_spriteFont.get());

	m_spriteBatch->End();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void ScreenManager::HandleInput(DX::StepTimer const& timer)
{
	m_gameMouse.HandleInput(timer);

	for (BaseScreen* screen : m_activeScreens)
	{
		// Screen input handling
		screen->HandleInput(timer);
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
void ScreenManager::AddScreen(BaseScreen* screenToAdd)
{
	screenToAdd->LoadContent();
	screenToAdd->Initialize();

	// push_front is a MUST
	// Subtle reason why - if we push_back, if we transition from one screen to another, we will handle input on that screen in the same update loop
	// This can lead to automatic button clicking if we transition from one screen to another via a button
	m_activeScreens.push_front(screenToAdd);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void ScreenManager::RemoveScreen(BaseScreen* screenToRemove)
{
	m_screensToDelete.push_back(screenToRemove);
}
