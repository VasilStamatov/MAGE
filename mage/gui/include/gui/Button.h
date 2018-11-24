#pragma once

#include "ecs/Component.h"
#include "math/Vec.h"
#include "renderer/GLTexture2D.h"

#include <functional>
#include <memory>

namespace mage
{
namespace gui
{

// ------------------------------------------------------------------------------

struct Button : public ecs::Component
{
  Button(math::Vec2i32 _screenPos, math::Vec2i32 _size);

  math::Vec2i32 m_screenPos;
  math::Vec2i32 m_size;
};

// ------------------------------------------------------------------------------

struct GUITexture : public ecs::Component
{
  GUITexture(std::shared_ptr<graphics::GLTexture2D> _texture);

  std::shared_ptr<graphics::GLTexture2D> m_texture;
};

// ------------------------------------------------------------------------------

struct GUICallback : public ecs::Component
{
  GUICallback(std::function<void()> _onClickCallback);

  std::function<void()> m_onClickCallback;
};

// ------------------------------------------------------------------------------

} // namespace gui
} // namespace mage