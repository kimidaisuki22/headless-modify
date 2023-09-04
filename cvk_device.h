#pragma once
#include <vector>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan.hpp>

vk::Instance create_simple_instance();

void print_physical_device_info(VkPhysicalDevice device);
std::vector<VkQueueFamilyProperties>
get_device_queue_props(VkPhysicalDevice device);

void print_queue_family_props_info(VkQueueFamilyProperties props);
