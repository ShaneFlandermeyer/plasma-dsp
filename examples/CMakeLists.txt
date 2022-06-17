# add_executable(dummy_target dummy_target.cpp)
# target_link_libraries(dummy_target PUBLIC plasma_dsp)
# target_include_directories(dummy_target PUBLIC ${CMAKE_SOURCE_DIR}/include)

# add_executable(fmcw_example fmcw_example.cpp)
# target_link_libraries(fmcw_example PUBLIC plasma_dsp)
# target_include_directories(fmcw_example PUBLIC ${CMAKE_SOURCE_DIR}/include)

# add_executable(cfar1d_example cfar1d_example.cpp)
# target_link_libraries(cfar1d_example PUBLIC plasma_dsp)
# target_include_directories(cfar1d_example PUBLIC ${CMAKE_SOURCE_DIR}/include)

# add_executable(cfar2d_example cfar2d_example.cpp)
# target_link_libraries(cfar2d_example PUBLIC plasma_dsp)
# target_include_directories(cfar2d_example PUBLIC ${CMAKE_SOURCE_DIR}/include)

# add_executable(pulse_compression pulse_compression.cc)
# target_link_libraries(pulse_compression PUBLIC plasma_dsp)


add_executable(fft_test fft_test.cpp)
target_link_libraries(fft_test PUBLIC plasma_dsp)
target_include_directories(fft_test PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(pulse_doppler pulse_doppler_processing.cc)
target_link_libraries(pulse_doppler PUBLIC plasma_dsp)