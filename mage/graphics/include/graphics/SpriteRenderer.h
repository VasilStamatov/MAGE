// #pragma once

// #include "Material.h"

// #include "ecs/RenderingSystem.h"

// namespace mage
// {
// namespace graphics
// {

// //
// ------------------------------------------------------------------------------

// struct SpriteComponent : public ecs::Component
// {
//   SpriteComponent(const std::string& _materialFile);

//   Material m_material;
// };

// //
// ------------------------------------------------------------------------------

// class SpriteRenderer : public ecs::RenderingSystem
// {
// public:
//   SpriteRenderer(GLShader _shader);

//   virtual void Render(mage::ecs::World& _world, const Camera& _camera,
//                       float _deltaTime) override;
// };

// //
// ------------------------------------------------------------------------------

// } // namespace graphics
// } // namespace mage