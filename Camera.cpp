#include "pch.h"
#include "Camera.h"
#include "ScreenManager.h"
#include "KeyboardInput.h"


//-----------------------------------------------------------------------------------------------------------------------------------
Camera::Camera() :
	m_cameraMode(CameraMode::kFixed),
	m_position(Vector2::Zero),
	m_panSpeed(300),
	m_zoom(1.0f)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
Camera::~Camera()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Camera::Update(DX::StepTimer const& timer)
{
	// If the camera is fixed we should not do any more updating
	if (m_cameraMode == CameraMode::kFixed)
	{
		return;
	}

	KeyboardInput& keyboard = ScreenManager::GetKeyboardInput();
	Vector2 diff = Vector2::Zero;

	if (keyboard.IsKeyDown(Keyboard::Keys::Left))
	{
		diff.x = -1;
	}
	if (keyboard.IsKeyDown(Keyboard::Keys::Right))
	{
		diff.x = 1;
	}
	if (keyboard.IsKeyDown(Keyboard::Keys::Up))
	{
		diff.y = -1;
	}
	if (keyboard.IsKeyDown(Keyboard::Keys::Down))
	{
		diff.y = 1;
	}

	if (diff != Vector2::Zero)
	{
		diff.Normalize();
		m_position += diff * (float)timer.GetElapsedSeconds() * m_panSpeed;
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
Matrix Camera::GetViewMatrix() const
{
	// It's -ve position because it is - don't change it
	return Matrix::CreateScale(m_zoom) * Matrix::CreateTranslation(-m_position.x, -m_position.y, 0);
}


//-----------------------------------------------------------------------------------------------------------------------------------
Vector2 Camera::ScreenToGameCoords(const Vector2 screenPosition) const
{
	Vector2 screenCentre = ScreenManager::GetScreenCentre();
	Vector2 tmp = (screenPosition - screenCentre) / m_zoom;				/// This is here because apparently the '/' operator returns XMVECTOR2 not Vector2
	return m_position + screenCentre - (m_zoom - 1) * screenCentre + tmp;
}


//-----------------------------------------------------------------------------------------------------------------------------------
Vector2 Camera::GameToScreenCoords(const Vector2 gamePosition) const
{
	Vector2 screenCentre = ScreenManager::GetScreenCentre();
	return screenCentre - m_position + (m_zoom - 1) * screenCentre + (gamePosition - screenCentre) * m_zoom;
}