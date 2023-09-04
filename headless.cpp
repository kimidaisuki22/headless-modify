#include "cvk_device.h"

#include <cstdint>
#include <iomanip>
#include <iostream>
#include <string>

void print_vulkan_api_version() {
  auto decodeAPIVersion = [](uint32_t apiVersion) -> std::string {
    return std::to_string(VK_VERSION_MAJOR(apiVersion)) + "." +
           std::to_string(VK_VERSION_MINOR(apiVersion)) + "." +
           std::to_string(VK_VERSION_PATCH(apiVersion));
  };

  uint32_t apiVersion = vk::enumerateInstanceVersion();
  std::cout << "APIVersion = " << decodeAPIVersion(apiVersion) << std::endl;
}

int main() {
  {
    print_vulkan_api_version();
    auto instance = create_simple_instance();
    // instance.createDebugUtilsMessengerEXT();
    auto devices = instance.enumeratePhysicalDevices();

    uint32_t count = devices.size();
    std::cout << "has " << count << " vk device.\n";
    for (uint32_t i = 0; i < count; i++) {

      std::cout << "Device " << i << ":" << std::endl;
      // print_physical_device_info(devices[i]);
      auto queue_props = devices[i].getQueueFamilyProperties();
      for (auto prop : queue_props) {
        std::cout << "queue count["<< std::setw(2) << prop.queueCount << "] props: ";
        std::cout << to_string(prop.queueFlags) << "\n";
      }
      std::cout << "-----------------------" << std::endl;
    }
  }
}