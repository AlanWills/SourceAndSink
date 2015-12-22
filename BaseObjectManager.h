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

///// DO NOT USE UNIQUE_PTRS HERE - IT DOES NOT WORK BECAUSE THE DESTRUCTORS ARE NOT SPECIFIED
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
	T* FindObject(const std::string& name);

	/// \brief Removes an object
	void RemoveObject(T* objectToRemove);

  /// \brief Gets all objects
  const std::list<T*>& GetObjects() const { return m_activeObjects; }

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
		for (T* object : m_activeObjects)
		{
			object->Die();
		}
	}

private:
	/// \brief Typedefs
	typedef std::list<T*> Objects;

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
	for (T* object : m_activeObjects)
	{
		object->LoadContent(m_device.Get());
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
template <typename T>
void BaseObjectManager<T>::Initialize()
{
	for (T* object : m_activeObjects)
	{
		object->Initialize();
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
template <typename T>
void BaseObjectManager<T>::Update(DX::StepTimer const& timer)
{
	for (T* object : m_activeObjects)
	{
		if (object->IsAlive())
		{
			object->Update(timer);
		}
		else
		{
			RemoveObject(object);
		}
	}

	for (T* object : m_objectsToDelete)
	{
		m_activeObjects.remove(object);
    delete object;
	}

	m_objectsToDelete.clear();
}


//-----------------------------------------------------------------------------------------------------------------------------------
template <typename T>
void BaseObjectManager<T>::Draw(SpriteBatch* spriteBatch, SpriteFont* spriteFont)
{
	for (T* object : m_activeObjects)
	{
		object->Draw(spriteBatch, spriteFont);
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
template <typename T>
void BaseObjectManager<T>::HandleInput(DX::StepTimer const& timer, const Vector2& mousePosition)
{
	for (T* object : m_activeObjects)
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

	m_activeObjects.push_back(objectToAdd);
}


//-----------------------------------------------------------------------------------------------------------------------------------
template <typename T>
T* BaseObjectManager<T>::FindObject(const std::string& name)
{
	for (T* object : m_activeObjects)
	{
		if (object->GetName() == name)
		{
			return object;
		}
	}

  return nullptr;
}


//-----------------------------------------------------------------------------------------------------------------------------------
template <typename T>
void BaseObjectManager<T>::RemoveObject(T* objectToRemove)
{
  if (objectToRemove->IsAlive())
  {
    objectToRemove->Die();
  }

	m_objectsToDelete.push_back(objectToRemove);
}