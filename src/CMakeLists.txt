add_library (cs4212-util
  ArgumentParsing.cpp ArgumentParsing.h
  handleGraphicsArgs.cpp handleGraphicsArgs.h
  model_obj.cpp model_obj.h
  Random.h Random.cpp
)

target_compile_definitions(cs4212-util PUBLIC HAS_GLM)
target_link_libraries(cs4212-util PRIVATE Boost::program_options)
target_link_libraries(cs4212-util PUBLIC glm::glm)

add_executable(fbMain
  fbMain.cpp
)
target_link_libraries(fbMain PRIVATE cs4212-util)
target_link_libraries(fbMain PRIVATE ${Boost_PROGRAM_OPTIONS_LIBRARIES})
target_link_libraries(fbMain PRIVATE PNG::PNG)
target_link_libraries(fbMain PRIVATE ZLIB::ZLIB)
