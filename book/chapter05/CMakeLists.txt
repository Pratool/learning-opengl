add_executable(logl_c5e1
    main.cpp
)

target_link_libraries(logl_c5e1
    utilities
)

install(TARGETS logl_c5e1
    EXPORT LearningOpenGLTargets
    RUNTIME DESTINATION bin
)
