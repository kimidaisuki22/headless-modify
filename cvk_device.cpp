#include "cvk_device.h"
#include <iostream>
#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_core.h>
#include <vulkan/vulkan_handles.hpp>
#include <vulkan/vulkan_to_string.hpp>

// #include <spdlog/spdlog.h>
vk::Instance create_simple_instance() {
  VkInstanceCreateInfo info{};
  info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  VkInstance ins;
  auto result = vkCreateInstance(&info, nullptr, &ins);
  // initialize the vk::ApplicationInfo structure
  vk::ApplicationInfo applicationInfo("APP", 1, "Engine", 1,
                                      VK_API_VERSION_1_1);

  // initialize the vk::InstanceCreateInfo
  vk::InstanceCreateInfo instanceCreateInfo({}, &applicationInfo);

  return vk::createInstance(instanceCreateInfo);
}

void print_physical_device_info(VkPhysicalDevice device) {
  VkPhysicalDeviceProperties prop{};
  vkGetPhysicalDeviceProperties(device, &prop);

  VkPhysicalDeviceMemoryProperties memProp{};
  vkGetPhysicalDeviceMemoryProperties(device, &memProp);

  VkPhysicalDeviceFeatures features{};
  vkGetPhysicalDeviceFeatures(device, &features);

  VkDisplayPropertiesKHR displays[164];
  uint32_t display_count{0};
  // vkGetPhysicalDeviceDisplayPropertiesKHR(devices[i],&display_count,displays);

  // VkPhysicalDeviceFormatProperties and
  // VkPhysicalDeviceDisplayPropertiesKHR require additional parameters.
  // This example will not cover those due to the complexity and potential
  // need for further array allocations.

  std::cout << "Name: " << prop.deviceName << std::endl;

  switch (prop.deviceType) {
  case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
    std::cout << "Type: Integrated GPU" << std::endl;
    break;
  case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
    std::cout << "Type: Discrete GPU" << std::endl;
    break;
  case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
    std::cout << "Type: Virtual GPU" << std::endl;
    break;
  case VK_PHYSICAL_DEVICE_TYPE_CPU:
    std::cout << "Type: CPU" << std::endl;
    break;
  default:
    std::cout << "Type: Other" << std::endl;
    break;
  }
  std::cout << "Api version: " << prop.apiVersion << "\n";
  std::cout << "Memory Heaps Count: " << memProp.memoryHeapCount << std::endl;
  for (uint32_t j = 0; j < memProp.memoryHeapCount; ++j) {
    std::cout << "Heap " << j << " size: " << memProp.memoryHeaps[j].size
              << std::endl;

    // Print out memory types for each heap.
    for (uint32_t k = 0; k < memProp.memoryTypeCount; ++k) {
      if (memProp.memoryTypes[k].heapIndex == j) {
        std::cout << "  Memory Type " << k << ":" << std::endl;

        uint32_t flags = memProp.memoryTypes[k].propertyFlags;
        std::cout << "    Property flags: ";
        if (flags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
          std::cout << "DEVICE_LOCAL ";
        if (flags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
          std::cout << "HOST_VISIBLE ";
        if (flags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
          std::cout << "HOST_COHERENT ";
        if (flags & VK_MEMORY_PROPERTY_HOST_CACHED_BIT)
          std::cout << "HOST_CACHED ";
        if (flags & VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT)
          std::cout << "LAZILY_ALLOCATED ";
        std::cout << std::endl;

        std::cout << "    Heap Index: " << memProp.memoryTypes[k].heapIndex
                  << std::endl;
      }
    }
  }

  // Tessellation Shader
  std::cout << "Tessellation Shader: "
            << (features.tessellationShader ? "Supported" : "Not Supported")
            << std::endl;

  // Geometry Shader
  std::cout << "Geometry Shader: "
            << (features.geometryShader ? "Supported" : "Not Supported")
            << std::endl;

  // Multi Viewport
  std::cout << "Multiple Viewports: "
            << (features.multiViewport ? "Supported" : "Not Supported")
            << std::endl;

  // Anisotropic Filtering
  std::cout << "Anisotropic Filtering: "
            << (features.samplerAnisotropy ? "Supported" : "Not Supported")
            << std::endl;

  // Texture Compression: ASTC LDR
  std::cout << "Texture Compression ASTC LDR: "
            << (features.textureCompressionASTC_LDR ? "Supported"
                                                    : "Not Supported")
            << std::endl;

  // Texture Compression: BC
  std::cout << "Texture Compression BC: "
            << (features.textureCompressionBC ? "Supported" : "Not Supported")
            << std::endl;

  // Independent Blend
  std::cout << "Independent Blend: "
            << (features.independentBlend ? "Supported" : "Not Supported")
            << std::endl;

  // Depth Bounds
  std::cout << "Depth Bounds: "
            << (features.depthBounds ? "Supported" : "Not Supported")
            << std::endl;

  // Fill Mode Non Solid
  std::cout << "Fill Mode Non Solid (Wireframe etc.): "
            << (features.fillModeNonSolid ? "Supported" : "Not Supported")
            << std::endl;

  // Pipeline statistics query
  std::cout << "Pipeline Statistics Query: "
            << (features.pipelineStatisticsQuery ? "Supported"
                                                 : "Not Supported")
            << std::endl;

  // ... and so on for other features you're interested in.

  // Continue with other properties as needed...

  for (uint32_t i{}; i < display_count; i++) {
    std::cout << displays[i].displayName
              << " width: " << displays[i].physicalResolution.width
              << " height: " << displays[i].physicalResolution.height << "\n";
  }
}
std::vector<VkQueueFamilyProperties>
get_device_queue_props(VkPhysicalDevice device) {
  uint32_t queueFamilyCount = 0;

  // First, query the number of queue families
  vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

  // Allocate space and fetch the queue family properties
  std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
  vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount,
                                           queueFamilies.data());

  return queueFamilies;
}
void print_queue_family_props_info(VkQueueFamilyProperties props) {
  // std::cout << VULKAN_HPP_NAMESPACE::to_string(props);
  std::cout << "Queue Count: " << props.queueCount << std::endl;
  std::cout << "Graphics Queue: "
            << ((props.queueFlags & VK_QUEUE_GRAPHICS_BIT) ? "Supported"
                                                           : "Not Supported")
            << std::endl;
  std::cout << "Compute Queue: "
            << ((props.queueFlags & VK_QUEUE_COMPUTE_BIT) ? "Supported"
                                                          : "Not Supported")
            << std::endl;
  std::cout << "Transfer Queue: "
            << ((props.queueFlags & VK_QUEUE_TRANSFER_BIT) ? "Supported"
                                                           : "Not Supported")
            << std::endl;
  std::cout << "Sparse Binding: "
            << ((props.queueFlags & VK_QUEUE_SPARSE_BINDING_BIT)
                    ? "Supported"
                    : "Not Supported")
            << std::endl;
  std::cout << "Video Decode: "
            << ((props.queueFlags & VK_QUEUE_VIDEO_DECODE_BIT_KHR)
                    ? "Supported"
                    : "Not Supported")
            << std::endl;

  std::cout << "Timestamp Bits: " << props.timestampValidBits << std::endl;

  // You can add more details here if required...
}