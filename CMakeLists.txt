cmake_minimum_required(VERSION 3.23.0)
project(tiny-vulkan VERSION 0.0.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
enable_testing()

find_package(Vulkan REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(tinyobjloader CONFIG REQUIRED)


add_library(cvk cvk_device.cpp)

target_link_libraries(cvk PUBLIC   glm::glm Vulkan::Vulkan
spdlog::spdlog
)



target_include_directories(cvk PUBLIC ${Stb_INCLUDE_DIR})
target_link_libraries(cvk PRIVATE tinyobjloader::tinyobjloader)




find_package(CLI11 CONFIG REQUIRED)




add_executable(headless headless.cpp)

target_link_libraries(headless PUBLIC
CLI11::CLI11
cvk
)
find_package(VulkanHeaders CONFIG)
target_link_libraries(cvk PRIVATE Vulkan::Headers)

# add_executable(render render.cpp)
# target_link_libraries(render PUBLIC
# cvk

# )
find_file(GLM_I_PATH glm.hpp)
include_directories(${CMAKE_BINARY_DIR}/vcpkg_installed/x64-linux/include)
include_directories(.)
find_package(Stb REQUIRED)
include_directories(${Stb_INCLUDE_DIR})
set(USE_HEADLESS)
add_subdirectory(Vulkan)