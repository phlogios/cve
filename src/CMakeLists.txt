file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/*.h")
file(GLOB SOURCE_LIST CONFIGURE_DEPENDS "*.cpp")

include_directories(
    ${PROJECT_SOURCE_DIR}/include/
	${GLFW_INCLUDE_DIR}
	${GLM_INCLUDE_DIR}
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

configure_file(${PROJECT_SOURCE_DIR}/include/CVEConfig.h.in ${PROJECT_SOURCE_DIR}/include/CVEConfig.h)

add_library(
    CVE
    ${SOURCE_LIST}
    ${HEADER_LIST}
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp ${IMGUI_DIR}/backends/imgui_impl_vulkan.cpp ${IMGUI_DIR}/imgui.cpp ${IMGUI_DIR}/imgui_draw.cpp ${IMGUI_DIR}/imgui_demo.cpp ${IMGUI_DIR}/imgui_tables.cpp ${IMGUI_DIR}/imgui_widgets.cpp
)

target_include_directories(CVE PUBLIC ../include)

target_link_libraries(CVE PRIVATE ${GLFW_LIBRARY} Vulkan::Vulkan)

target_compile_features(CVE PUBLIC cxx_std_17)

source_group(
    TREE "${PROJECT_SOURCE_DIR}/include"
    PREFIX "Header Files"
    FILES ${HEADER_LIST}
)

target_include_directories(CVE PUBLIC
	"${PROJECT_BINARY_DIR}"
)