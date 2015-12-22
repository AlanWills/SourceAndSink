#pragma once

#include "Texture2D.h"
#include "StepTimer.h"
#include "Collider.h"
#include "MouseButton.h"

using namespace DirectX::SimpleMath;

class BaseObject
{
public:
	enum LoadType
	{
		kData,
		kTexture,
		kNoLoad
	};

	BaseObject(const std::string& dataAsset, LoadType = LoadType::kData, BaseObject* parent = nullptr);
	BaseObject(const Vector2& localPosition, const std::string& dataAsset, LoadType = LoadType::kData, BaseObject* parent = nullptr);
	BaseObject(const Vector2& size, const Vector2& localPosition, const std::string& dataAsset, LoadType = LoadType::kData, BaseObject* parent = nullptr);
	
	virtual ~BaseObject();

	/// \brief Loads the data (if it exists) and texture for the object
	virtual void LoadContent(ID3D11Device* device);

  /// \brief Uses the inputted char* to load a texture to the texture handler
  void LoadTexture(ID3D11Device* device, const std::string& textureAsset);

	/// \brief Initializes data before update begins
	virtual void Initialize();

	/// \brief Adds by default a rectangle collider
	virtual void AddCollider();

	/// \brief Update the logic of the object
	virtual void Update(DX::StepTimer const& timer);

	/// \brief Draw the object in world space
	virtual void Draw(SpriteBatch* spriteBatch, SpriteFont* spriteFont);

	/// \brief Handle input from elsewhere and update this object's mouse over and selection status
	virtual void HandleInput(DX::StepTimer const& timer, const Vector2& mousePosition);

	/// \brief Returns a pointer to the parent of this object
	BaseObject* GetParent() { return m_parent; }

	/// \brief Returns a pointer to the parent of this object as an inputted type
	template <typename T>
	T* GetParentAs() { return dynamic_cast<T*>(m_parent); }

	/// \brief State Utility Functions
	bool IsActive() { return m_active; }
	bool IsVisible() { return m_visible; }
	bool AcceptsInput() { return m_acceptsInput; }
	bool IsAlive() { return m_alive; }

	void SetActive(bool active) { m_active = active; }
	void SetVisible(bool visible) { m_visible = visible; }
	void SetAcceptsInput(bool acceptsInput) { m_acceptsInput = acceptsInput; }
	void SetAlive(bool alive) { m_alive = alive; }
	
	/// \brief Sets active, visible, acceptsinput and alive to true and creates a collider
	void Create();

	// \brief Sets active, visible and acceptsinput to true
	void Show()
	{
		SetActive(true);
		SetVisible(true);
		SetAcceptsInput(true);
	}

	/// \brief Sets active, visible and acceptsinput to false
	void Hide()
	{
		SetActive(false);
		SetVisible(false);
		SetAcceptsInput(false);
	}

	/// \brief Sets active, visible, acceptsinput and alive to false
	virtual void Die();

	/// \brief Transform utility functions
	/// GetWorldPosition cannot return a reference as we are returning the result of a calculation
	const Vector2 GetWorldPosition() const;
	const Vector2 GetWorldPosition(const Vector2& localPosition) const;
	const float GetWorldRotation() const;

	const Vector2& GetLocalPosition() const { return m_localPosition; }
	void SetLocalPosition(const Vector2& localPosition) { m_localPosition = localPosition; }

	float GetLocalRotation() const { return m_localRotation; }
	void SetLocalRotation(const float localRotation) { m_localRotation = XMScalarModAngle(localRotation); }

	const std::string& GetName() const { return m_name; }
	void SetName(const std::string& name) { m_name = name; }

	const Vector2& GetSize() const { return m_size; }
	void SetSize(const Vector2& size) { m_size = size; }

	const bool IsSelected(const MouseButton mouseButton = MouseButton::kLeftButton) const { return m_selected[static_cast<unsigned int>(mouseButton)]; }
  void SetSelected(const bool selected, const MouseButton mouseButton)
  {
    assert(mouseButton < MouseButton::kNumButtons);
    m_selected[static_cast<unsigned int>(mouseButton)] = selected;
  }

  const bool IsClicked(const MouseButton mouseButton = MouseButton::kLeftButton) const { return m_clicked[static_cast<unsigned int>(mouseButton)]; }
  void SetClicked(const bool clicked, const MouseButton mouseButton)
  { 
    assert(mouseButton < MouseButton::kNumButtons);
    m_clicked[static_cast<unsigned int>(mouseButton)] = clicked;
  }

  /// \brief Function to set all clicked entries to false
  void FlushClickArray();

  /// \brief Function to set all selected entries to false
  void FlushSelectArray();

	void SetColour(const Color& colour) { m_colour = colour; }

	const float GetOpacity() const { return m_opacity; }
	void SetOpacity(const float opacity) { m_opacity = opacity; }

	Collider* GetCollider() const { return m_collider.get(); }

  const std::string& GetDataAsset() const { return m_dataAsset; }

  /// \brief Set the on death function for this object
  void SetOnDeathFunction(const std::function<void()>& onDeathFunction) { m_onDeathFunction = onDeathFunction; }

protected:

	/// \brief Gets the texture handler - cannot be const because draw is non-const (for now)
	virtual Texture2D* GetTexture() const { return m_textureHandler.get(); }

	const bool IsMouseOver() const { return m_mouseOver; }
	void SetMouseOver(const bool mouseOver) { m_mouseOver = mouseOver; }

	const Color& GetColour() const { return m_colour; }

private:
	// Used to work out whether we should load an XML file or just a texture
	LoadType m_loadType;

	// Data asset
  std::string m_dataAsset;

	// A string to identify the object
	std::string m_name;

	// Local position from parent
	Vector2 m_localPosition;

	// Local rotation from parent
	float m_localRotation;

	// Texture and size
	std::unique_ptr<Texture2D> m_textureHandler;
	Vector2 m_size;

	// State variables
	bool m_active;			// If true the object updates
	bool m_visible;			// If true the object is drawn
	bool m_acceptsInput;	// If true the object accepts input
	bool m_alive;			// If false the object will be destroyed

	// Colour variables
	Color m_colour;
	float m_opacity;

	// Used for handling input - variables to represent whether the mouse is over the object
	// And whether it is selected
  // And whether it has just been clicked - will only last one loop from when it was selected
	bool m_mouseOver;
	bool m_selected[static_cast<unsigned int>(MouseButton::kNumButtons)];
  bool m_clicked[static_cast<unsigned int>(MouseButton::kNumButtons)];

	// Collider
	std::unique_ptr<Collider> m_collider;

	// Parent object pointer
	BaseObject* m_parent;

  /// \brief Callback function for when this object dies - allows custom behaviour when ths object dies
  std::function<void()> m_onDeathFunction;
};

