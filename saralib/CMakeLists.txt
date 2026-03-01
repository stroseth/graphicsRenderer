include_directories(${CMAKE_SOURCE_DIR}/src)

add_library (saralib
    vec3.h
    Framebuffer.h Framebuffer.cpp
    ray.h
    Camera.h Camera.cpp 
    PerspectiveCamera.h PerspectiveCamera.cpp
    Shape.h
)
target_link_libraries(saralib PRIVATE cs4212-util)

add_executable(main
    fbMain.cpp
)

target_link_libraries(main saralib)
target_link_libraries(main cs4212-util)
target_link_libraries(main ${Boost_PROGRAM_OPTIONS_LIBRARIES})
target_link_libraries(main PNG::PNG)
target_link_libraries(main ZLIB::ZLIB)