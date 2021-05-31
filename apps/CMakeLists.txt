include_directories(
	${GLFW_INCLUDE_DIR}
	${GLM_INCLUDE_DIR}
)

add_executable(app main.cpp)
target_compile_features(app PRIVATE cxx_std_17)
target_link_libraries(app PRIVATE CVE Vulkan::Vulkan)

add_custom_command(TARGET app PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:app>/resources)
