add_executable(dummy_target dummy_target.cpp)
target_link_libraries(dummy_target PUBLIC Matplot++::matplot plasma-dsp)
target_include_directories(dummy_target PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(fmcw_example fmcw_example.cpp)
target_link_libraries(fmcw_example PUBLIC Matplot++::matplot plasma-dsp)
target_include_directories(fmcw_example PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(cfar1d_example cfar1d_example.cpp)
target_link_libraries(cfar1d_example PUBLIC Matplot++::matplot plasma-dsp)
target_include_directories(cfar1d_example PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(cfar2d_example cfar2d_example.cpp)
target_link_libraries(cfar2d_example PUBLIC Matplot++::matplot plasma-dsp)
target_include_directories(cfar2d_example PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(pulse_compression pulse_compression.cc)
target_link_libraries(pulse_compression PUBLIC Matplot++::matplot plasma-dsp)
target_include_directories(pulse_compression PUBLIC ${CMAKE_SOURCE_DIR}/include)