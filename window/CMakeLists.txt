find_package(glfw3 REQUIRED)

add_executable(window
    main.cpp
)

target_link_libraries(window
    glad
    glfw
)

install(TARGETS window
    EXPORT LearningOpenGLTargets
    RUNTIME DESTINATION bin
)
