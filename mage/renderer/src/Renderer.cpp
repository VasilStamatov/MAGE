// #include "renderer/Renderer.h"

// #include "exceptions/RuntimeError.h"

// #include <cstdint>
// #include <iostream>
// #include <vector>

// #define GLFW_INCLUDE_VULKAN
// #include <glfw3.h>

// namespace mage
// {
// namespace renderer
// {

// //
// ------------------------------------------------------------------------------

// namespace
// {

// //
// ------------------------------------------------------------------------------

// // Additional validation layers for bug-catching in DEBUG mode
// const std::vector<const char*> c_validationLayers = {
//     "VK_LAYER_LUNARG_standard_validation"};

// //
// ------------------------------------------------------------------------------

// #ifdef NDEBUG
// constexpr bool enableValidationLayers = false;
// #else
// constexpr bool enableValidationLayers = true;
// #endif

// //
// ------------------------------------------------------------------------------

// std::string
// DebugMessageTypeToString(VkDebugUtilsMessageTypeFlagsEXT _messageType)
// {
//   switch (_messageType)
//   {
//     case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT:
//       return "Some event has happened that is unrelated to the specification
//       "
//              "or performance";
//     case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT:
//       return "Something has happened that violates the specification or "
//              "indicates a possible mistake";
//     case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT:
//       return "Potential non-optimal use of Vulkan";
//   }
//   return "Unexpected Type";
// }

// //
// ------------------------------------------------------------------------------

// VKAPI_ATTR VkBool32 VKAPI_CALL
// DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT _messageSeverity,
//               VkDebugUtilsMessageTypeFlagsEXT _messageType,
//               const VkDebugUtilsMessengerCallbackDataEXT* _pCallbackData,
//               void* _pUserData)
// {
//   // switch (_messageSeverity)
//   // {
//   //   case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
//   //     // Diagnostic
//   //     break;
//   //   case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
//   //     // Info
//   //     break;
//   //   case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
//   //     // Warning
//   //     break;
//   //   case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
//   //     // Error
//   //     break;
//   // }

//   // std::cout << DebugMessageTypeToString(_messageType) << std::endl;
//   std::cerr << "validation layer: " << _pCallbackData->pMessage << std::endl;

//   return VK_FALSE;
// }

// //
// ------------------------------------------------------------------------------

// VkResult CreateDebugUtilsMessengerEXT(
//     VkInstance _instance,
//     const VkDebugUtilsMessengerCreateInfoEXT* _pCreateInfo,
//     const VkAllocationCallbacks* _pAllocator,
//     VkDebugUtilsMessengerEXT* _pCallback)
// {
//   auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
//       _instance, "vkCreateDebugUtilsMessengerEXT");

//   if (func != nullptr)
//   {
//     return func(_instance, _pCreateInfo, _pAllocator, _pCallback);
//   }
//   else
//   {
//     return VK_ERROR_EXTENSION_NOT_PRESENT;
//   }
// }

// //
// ------------------------------------------------------------------------------

// void DestroyDebugUtilsMessengerEXT(VkInstance _instance,
//                                    VkDebugUtilsMessengerEXT _callback,
//                                    const VkAllocationCallbacks* _pAllocator)
// {
//   auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
//       _instance, "vkDestroyDebugUtilsMessengerEXT");

//   if (func != nullptr)
//   {
//     func(_instance, _callback, _pAllocator);
//   }
// }

// //
// ------------------------------------------------------------------------------

// } // namespace

// //
// ------------------------------------------------------------------------------

// class Renderer::Impl
// {
// public:
//   void Initialize();

//   //
//   ------------------------------------------------------------------------------

//   void Shutdown();

//   //
//   ------------------------------------------------------------------------------

// private:
//   void CreateInstance();

//   //
//   ------------------------------------------------------------------------------

//   void SetupDebugCallback();

//   //
//   ------------------------------------------------------------------------------

//   bool CheckValidationLayerSupport();

//   //
//   ------------------------------------------------------------------------------

//   std::vector<const char*> GetRequiredExtensions();

//   //
//   ------------------------------------------------------------------------------

//   void EnsureAllRequiredExtensionsArePresent(
//       const std::vector<const char*>& _requiredExtensions,
//       const std::vector<VkExtensionProperties>& _availableExtensions);

//   //
//   ------------------------------------------------------------------------------

// private:
//   VkInstance m_instance;
//   VkDebugUtilsMessengerEXT m_callback;
// };

// //
// ------------------------------------------------------------------------------

// Renderer::Renderer()
//     : m_impl(std::make_unique<Impl>())
// {
// }

// //
// ------------------------------------------------------------------------------

// Renderer::~Renderer() {}

// //
// ------------------------------------------------------------------------------

// void Renderer::Initialize() { m_impl->Initialize(); }

// //
// ------------------------------------------------------------------------------

// void Renderer::Shutdown() { m_impl->Shutdown(); }

// //
// ------------------------------------------------------------------------------
// //                              IMPLEMENTATION
// //
// ------------------------------------------------------------------------------

// void Renderer::Impl::Initialize()
// {
//   CreateInstance();
//   SetupDebugCallback();
// }

// //
// ------------------------------------------------------------------------------

// void Renderer::Impl::Shutdown()
// {
//   // if (enableValidationLayers)
//   // {
//   //   DestroyDebugUtilsMessengerEXT(m_instance, m_callback, nullptr);
//   // }

//   vkDestroyInstance(m_instance, nullptr);
// }

// //
// ------------------------------------------------------------------------------

// void Renderer::Impl::CreateInstance()
// {
//   if constexpr (enableValidationLayers)
//   {
//     if (CheckValidationLayerSupport() == false)
//     {
//       throw RUNTIME_ERROR("validation layers requested, but not available!");
//     }
//   }

//   // optional
//   VkApplicationInfo appInfo = {};
//   appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
//   appInfo.pApplicationName = "MAGE";
//   appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
//   appInfo.pEngineName = "No Engine";
//   appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
//   appInfo.apiVersion = VK_API_VERSION_1_0;

//   // compulsory
//   VkInstanceCreateInfo createInfo = {};
//   createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
//   createInfo.pApplicationInfo = &appInfo;

//   // get required extensions
//   auto requiredExtensions = GetRequiredExtensions();

//   createInfo.enabledExtensionCount =
//       static_cast<std::uint32_t>(requiredExtensions.size());
//   createInfo.ppEnabledExtensionNames = requiredExtensions.data();

//   // get available extensions
//   std::uint32_t availableExtensionCount = 0;
//   vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionCount,
//                                          nullptr);

//   std::vector<VkExtensionProperties> availableExtensions(
//       availableExtensionCount);

//   vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionCount,
//                                          availableExtensions.data());

//   std::cout << "Available extensions:" << std::endl;

//   for (const auto& extension : availableExtensions)
//   {
//     std::cout << "\t" << extension.extensionName << std::endl;
//   }

//   // ensure are required extensions are also available
//   EnsureAllRequiredExtensionsArePresent(requiredExtensions,
//                                         availableExtensions);

//   // set global validation layers
//   if constexpr (enableValidationLayers)
//   {
//     createInfo.enabledLayerCount =
//         static_cast<uint32_t>(c_validationLayers.size());
//     createInfo.ppEnabledLayerNames = c_validationLayers.data();
//   }
//   else
//   {
//     createInfo.enabledLayerCount = 0;
//   }

//   if (vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS)
//   {
//     throw RUNTIME_ERROR("Failed to create vulkan instance");
//   }
// }

// //
// ------------------------------------------------------------------------------

// void Renderer::Impl::SetupDebugCallback()
// {
//   if constexpr (enableValidationLayers)
//   {
//     VkDebugUtilsMessengerCreateInfoEXT createInfo = {};

//     createInfo.sType =
//     VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

//     createInfo.messageSeverity =
//         VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
//         VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
//         VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

//     createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
//                              VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
//                              VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

//     createInfo.pfnUserCallback = DebugCallback;
//     createInfo.pUserData = nullptr;

//     if (CreateDebugUtilsMessengerEXT(m_instance, &createInfo, nullptr,
//                                      &m_callback) != VK_SUCCESS)
//     {
//       throw RUNTIME_ERROR("failed to set up debug callback!");
//     }
//   }
// }

// //
// ------------------------------------------------------------------------------

// bool Renderer::Impl::CheckValidationLayerSupport()
// {
//   std::uint32_t layerCount;
//   vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

//   std::vector<VkLayerProperties> availableLayers(layerCount);
//   vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

//   for (const auto& validationLayer : c_validationLayers)
//   {
//     bool found = false;

//     for (const auto& layer : availableLayers)
//     {
//       if (strcmp(validationLayer, layer.layerName) == 0)
//       {
//         found = true;
//         break;
//       }
//     }

//     if (!found)
//     {
//       return false;
//     }
//   }

//   return true;
// }

// //
// ------------------------------------------------------------------------------

// std::vector<const char*> Renderer::Impl::GetRequiredExtensions()
// {
//   std::uint32_t glfwExtensionCount = 0u;
//   const char** glfwExtensions =
//       glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

//   std::vector<const char*> extensions(glfwExtensions,
//                                       glfwExtensions + glfwExtensionCount);

//   if constexpr (enableValidationLayers)
//   {
//     extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
//   }

//   std::cout << "Required extensions:" << std::endl;
//   for (const auto& extension : extensions)
//   {
//     std::cout << "\t" << extension << std::endl;
//   }

//   return extensions;
// }

// //
// ------------------------------------------------------------------------------

// void Renderer::Impl::EnsureAllRequiredExtensionsArePresent(
//     const std::vector<const char*>& _requiredExtensions,
//     const std::vector<VkExtensionProperties>& _availableExtensions)
// {
//   for (const auto& requiredExtension : _requiredExtensions)
//   {
//     bool found = false;

//     for (const auto& availableExtension : _availableExtensions)
//     {
//       if (strcmp(requiredExtension, availableExtension.extensionName) == 0)
//       {
//         found = true;
//         break;
//       }
//     }

//     if (!found)
//     {
//       throw RUNTIME_ERROR("missing vulkan extension");
//     }
//   }
// }

// //
// ------------------------------------------------------------------------------

// } // namespace renderer
// } // namespace mage