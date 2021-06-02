cmake_minimum_required(VERSION 3.10)

# set the project name
project(
	CVE
	VERSION 1.0
	DESCRIPTION "A cross-platform Vulkan rendering engine"
	LANGUAGES CXX
)


if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	set(CMAKE_CXX_STANDARD 17)
	set(CMAKE_CXX_STANDARD_REQUIRED True)

	# Let's nicely support folders in IDEs
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)

endif()

if (APPLE)
	set(ENV{VULKAN_SDK} /users/gustav/development/libs/vulkansdk-macos-1.2.162.0/macOS)
	set(ENV{VK_LAYER_PATH} $ENV{VULKAN_SDK}/share/vulkan/explicit_layer.d)
	set(ENV{VK_ICD_FILENAMES} $ENV{VULKAN_SDK}/share/vulkan/icd.d/MoltenVK_icd.json)
endif()

if (WIN32)
	set(glfw3_DIR "C:\\Development\\Libraries\\glfw-3.3.2.bin.WIN64")
	set(GLM_INCLUDE_DIR "C:\\Development\\Libraries\\glm-0.9.9.8\\glm")

	set(GLFW_LIBRARY ${glfw3_DIR}/lib-vc2019/glfw3.lib)
	set(GLFW_INCLUDE_DIR ${glfw3_DIR}/include)
endif()

set(IMGUI_DIR ${PROJECT_SOURCE_DIR}/dependencies/imgui)

find_package(Vulkan REQUIRED)

# engine code is here
add_subdirectory(src)

# apps code is here
add_subdirectory(apps)