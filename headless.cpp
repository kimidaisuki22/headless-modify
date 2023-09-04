#include "cvk_device.h"
#include "print.h"
#include <cstdint>
#include <iostream>

int main() {
  {
    auto instance = create_simple_instance();
    auto devices = enumerate_physical_devices(instance);

    uint32_t count = devices.size();
    std::cout << "has " << count << " vk device.\n";
    for (uint32_t i = 0; i < count; i++) {

      std::cout << "Device " << i << ":" << std::endl;
      print_physical_device_info(devices[i]);
      print_elem_array(get_device_queue_props(devices[i]),
                       print_queue_family_props_info, "Queue props");

      std::cout << "-----------------------" << std::endl;
    }
  }
}