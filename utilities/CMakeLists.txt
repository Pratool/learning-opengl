find_package(glfw3 REQUIRED)

add_library(utilities INTERFACE)

target_include_directories(utilities INTERFACE
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(utilities INTERFACE
    glad
    glfw
)
