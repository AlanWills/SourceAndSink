#pragma once

#include "StepTimer.h"
#include "SpriteBatch.h"

#include "GameMouse.h"
#include "KeyboardInput.h"

#include <DirectXCollision.h>
#include <list>

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

template <typename T> class BaseObjectManager
{
public:
	BaseObjectManager(Microsoft::WRL::ComPtr<ID3D11Device> device);
	~BaseObjectManager();

	/// \brief Adds necessary objects and loads content of all active objects
	void LoadContent();

	/// \brief Initializes all active objects
	void Initialize();

	/// \brief Update all active objects and add/remove any necessary objects
	void Update(DX::StepTimer const& timer);

	/// \brief Draws all active objects
	void Draw(SpriteBatch* spriteBatch, SpriteFont* spriteFont);

	/// \brief Handles input for all active objects
	void HandleInput(DX::StepTimer const& timer, const Vector2& mousePosition);

	/// \brief Adds an object 
	void AddObject(T* objectToAdd, bool load = false, bool initialize = false);

	/// \brief Find an object with a specific tag
	T* FindObject(const std::wstring& tag);

	/// \brief Removes an object
	void RemoveObject(T* objectToRemove);

  /// \brief Gets all objects
  const std::list<std::unique_ptr<T>>& GetObjects() const { return m_activeObjects; }

	/// \brief Calls Show() on each active object
	void ShowAll()
	{
		for (auto& object : m_activeObjects)
		{
			object->Show();
		}
	}

	/// \brief Calls Hide() on each active object
	void HideAll()
	{
		for (auto& object : m_activeObjects)
		{
			object->Hide();
		}
	}

	/// \brief Calls Die() on each active object
	void DieAll()
	{
		for (auto& object : m_activeObjects)
		{
			object->Die();
		}
	}

private:
	/// \brief Typedefs
	typedef std::list<std::unique_ptr<T>> Objects;

	Objects m_activeObjects;
	Objects m_objectsToDelete;

	Microsoft::WRL::ComPtr<ID3D11Device> m_device;
};


///////////// TEMPLATED FUNCTION DEFINITIONS

//-----------------------------------------------------------------------------------------------------------------------------------
template <typename T>
BaseObjectManager<T>::BaseObjectManager(Microsoft::WRL::ComPtr<ID3D11Device> device) :
	m_device(device)
{

}


//-----------------------------------------------------------------------------------------------------------------------------------
template <typename T>
BaseObjectManager<T>::~BaseObjectManager()
{
	m_activeObjects.clear();
	m_objectsToDelete.clear();
}


//-----------------------------------------------------------------------------------------------------------------------------------
template <typename T>
void BaseObjectManager<T>::LoadContent()
{
	for (auto& object : m_activeObjects)
	{
		object->LoadContent(m_device.Get());
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
template <typename T>
void BaseObjectManager<T>::Initialize()
{
	for (auto& object : m_activeObjects)
	{
		object->Initialize();
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
template <typename T>
void BaseObjectManager<T>::Update(DX::StepTimer const& timer)
{
	for (auto& object : m_activeObjects)
	{
		if (object->IsAlive())
		{
			object->Update(timer);
		}
		else
		{
			RemoveObject(object.get());
		}
	}

	for (auto& object : m_objectsToDelete)
	{
		m_activeObjects.remove(object);
	}

	m_objectsToDelete.clear();
}


//-----------------------------------------------------------------------------------------------------------------------------------
template <typename T>
void BaseObjectManager<T>::Draw(SpriteBatch* spriteBatch, SpriteFont* spriteFont)
{
	for (auto& object : m_activeObjects)
	{
		object->Draw(spriteBatch, spriteFont);
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
template <typename T>
void BaseObjectManager<T>::HandleInput(DX::StepTimer const& timer, const Vector2& mousePosition)
{
	for (auto& object : m_activeObjects)
	{
		object->HandleInput(timer, mousePosition);
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
template <typename T>
void BaseObjectManager<T>::AddObject(T* objectToAdd, bool load, bool initialize)
{
	if (load)
	{
		objectToAdd->LoadContent(m_device.Get());
	}

	if (initialize)
	{
		objectToAdd->Initialize();
	}

	m_activeObjects.push_back(std::unique_ptr<T>(objectToAdd));
}


//-----------------------------------------------------------------------------------------------------------------------------------
template <typename T>
T* BaseObjectManager<T>::FindObject(const std::wstring& tag)
{
	for (auto& object : m_activeObjects)
	{
		if (object->m_tag == tag)
		{
			return object;
		}
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
template <typename T>
void BaseObjectManager<T>::RemoveObject(T* objectToRemove)
{
	objectToRemove->Die();
	m_objectsToDelete.push_back(std::unique_ptr<T>(objectToRemove));
}