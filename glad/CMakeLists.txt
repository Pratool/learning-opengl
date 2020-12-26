add_library(glad
    src/glad.c
)

target_include_directories(glad
    PUBLIC $<INSTALL_INTERFACE:include>
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

install(TARGETS glad
    EXPORT LearningOpenGLTargets
    ARCHIVE DESTINATION lib
)
