#include "cvk_device.h"
#include "print.h"
#include <cstdint>
#include <iostream>
#include <string>

int main() {
  {
    auto instance = create_simple_instance();
    // instance.createDebugUtilsMessengerEXT();
    // auto devices = enumerate_physical_devices(instance);
    auto devices = instance.enumeratePhysicalDevices();

    uint32_t count = devices.size();
    std::cout << "has " << count << " vk device.\n";
    for (uint32_t i = 0; i < count; i++) {

      std::cout << "Device " << i << ":" << std::endl;
      // print_physical_device_info(devices[i]);
      auto queue_props = devices[i].getQueueFamilyProperties();
      for (auto prop : queue_props) {
        std::cout << "queue count: " << prop.queueCount << "\n";
        std::cout << to_string(prop.queueFlags) << "\n";
        std::cout << std::string(32, '-') << "\n";
      }
      std::cout << "-----------------------" << std::endl;
    }
  }
}