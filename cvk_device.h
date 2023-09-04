#pragma once
#include <vector>
#include <vulkan/vulkan.h>

VkInstance create_simple_instance();
std::vector<VkPhysicalDevice> enumerate_physical_devices(VkInstance instance);
void print_physical_device_info(VkPhysicalDevice device);
std::vector<VkQueueFamilyProperties>
get_device_queue_props(VkPhysicalDevice device);

void print_queue_family_props_info(VkQueueFamilyProperties props);
