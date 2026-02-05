include_directories(${CMAKE_SOURCE_DIR}/src)

add_library (saralib
    vec3.h
    Framebuffer.h
    Framebuffer.cpp
)
target_link_libraries(saralib PRIVATE cs4212-util)