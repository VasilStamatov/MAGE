// #include "graphics/SpriteRenderer.h"

// #include "ecs/World.h"
// #include "ecs_common/TransformComponent.h"

// namespace mage
// {
// namespace graphics
// {

// //
// ------------------------------------------------------------------------------

// SpriteComponent::SpriteComponent(const std::string& _materialFile)
//     : m_material(_materialFile)
// {
// }

// //
// ------------------------------------------------------------------------------

// SpriteRenderer::SpriteRenderer(GLShader _shader)
//     : ecs::RenderingSystem(std::move(_shader))
// {
//   m_systemSignature.AddComponent<ecs::common::TransformComponent>();
//   m_systemSignature.AddComponent<SpriteComponent>();
// }

// //
// ------------------------------------------------------------------------------

// void SpriteRenderer::Render(mage::ecs::World& _world, const Camera& _camera,
//                             float _deltaTime)
// {
//   m_shader.Bind();
//   m_shader.SetUniformMat4("in_Projection", _camera.GetProjection());
//   m_shader.SetUniformMat4("in_View", _camera.GetView());

//   for (auto&& entity : m_registeredEntities)
//   {
//     auto& transform =
//         _world.GetComponent<ecs::common::TransformComponent>(entity);
//   }
// }

// //
// ------------------------------------------------------------------------------

// } // namespace graphics
// } // namespace mage