cmake_minimum_required(VERSION 3.10)

# set the project name
project(CVE VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(src/CVEConfig.h.in CVEConfig.h)

set(ENV{VULKAN_SDK} /users/gustav/development/libs/vulkansdk-macos-1.2.162.0/macOS)
set(ENV{VK_LAYER_PATH} $ENV{VULKAN_SDK}/share/vulkan/explicit_layer.d)
set(ENV{VK_ICD_FILENAMES} $ENV{VULKAN_SDK}/share/vulkan/icd.d/MoltenVK_icd.json)

find_package(glfw3 REQUIRED)
find_package(vulkan REQUIRED)

# add the executable
add_executable(CVE src/main.cpp)

target_link_libraries(CVE glfw Vulkan::Vulkan)

target_include_directories(CVE PUBLIC
	"${PROJECT_BINARY_DIR}"
	)
