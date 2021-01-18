find_package(glfw3 REQUIRED)

add_executable(6837a0
    main.cpp
)

target_link_libraries(6837a0
    glad
    glfw
)

install(TARGETS 6837a0
    EXPORT LearningOpenGLTargets
    RUNTIME DESTINATION bin
)
