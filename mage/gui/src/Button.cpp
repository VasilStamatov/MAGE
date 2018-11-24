#include "gui/Button.h"

namespace mage
{
namespace gui
{

// ------------------------------------------------------------------------------

Button::Button(math::Vec2i32 _screenPos, math::Vec2i32 _size)
    : m_screenPos(_screenPos)
    , m_size(_size)
{
}

// ------------------------------------------------------------------------------

GUITexture::GUITexture(std::shared_ptr<graphics::GLTexture2D> _texture)
    : m_texture(_texture)
{
}

// ------------------------------------------------------------------------------

GUICallback::GUICallback(std::function<void()> _onClickCallback)
    : m_onClickCallback(_onClickCallback)
{
}

// ------------------------------------------------------------------------------

} // namespace gui
} // namespace mage