include_directories(${CMAKE_SOURCE_DIR}/src)

add_library (saralib
    vec3.h
    Framebuffer.h Framebuffer.cpp
    ray.h
    Camera.h Camera.cpp 
    PerspectiveCamera.h PerspectiveCamera.cpp
    Shape.h
    HitStruct.h 
    Sphere.h Sphere.cpp 
    Triangle.h Triangle.cpp
    PointLight.h
    Shader.h
    NormalShader.h NormalShader.cpp
    LambertianShader.h LambertianShader.cpp
    BlinnPhongShader.h BlinnPhongShader.cpp
    RayTracer.h RayTracer.cpp
    MirrorShader.h MirrorShader.cpp
    DiffuseShader.h DiffuseShader.cpp
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