file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${CVE_SOURCE_DIR}/include/*.h")
file(GLOB SOURCES CONFIGURE_DEPENDS "*.cpp")

include_directories(
    ${CVE_SOURCE_DIR}/include/
	${GLFW_INCLUDE_DIR}
	${GLM_INCLUDE_DIR}
)

configure_file(${CVE_SOURCE_DIR}/include/CVEConfig.h.in CVEConfig.h)

add_library(CVE ${SOURCES} ${HEADERS})

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