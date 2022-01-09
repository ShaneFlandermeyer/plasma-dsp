add_executable(dummy-target dummy-target.cpp)
target_link_libraries(dummy-target PUBLIC Matplot++::matplot plasma-dsp)
target_include_directories(dummy-target PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(fmcw-example fmcw-example.cpp)
target_link_libraries(fmcw-example PUBLIC Matplot++::matplot plasma-dsp)
target_include_directories(fmcw-example PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(cfar1d-example cfar1d-example.cpp)
target_link_libraries(cfar1d-example PUBLIC Matplot++::matplot plasma-dsp)
target_include_directories(cfar1d-example PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(cfar2d-example cfar1d-example.cpp)
target_link_libraries(cfar2d-example PUBLIC Matplot++::matplot plasma-dsp)
target_include_directories(cfar2d-example PUBLIC ${CMAKE_SOURCE_DIR}/include)