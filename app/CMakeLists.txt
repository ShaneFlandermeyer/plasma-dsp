add_executable(test_target main.cpp)
target_link_libraries(test_target PUBLIC Matplot++::matplot plasma-dsp)
target_include_directories(test_target PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(fmcw fmcw_driver.cpp)
target_link_libraries(fmcw PUBLIC Matplot++::matplot plasma-dsp)
target_include_directories(fmcw PUBLIC ${CMAKE_SOURCE_DIR}/include)
