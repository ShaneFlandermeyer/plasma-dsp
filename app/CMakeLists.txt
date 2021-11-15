add_executable(test_target main.cpp)
target_link_libraries(test_target PUBLIC Matplot++::matplot waveform)
target_include_directories(test_target PUBLIC ${CMAKE_SOURCE_DIR}/include)