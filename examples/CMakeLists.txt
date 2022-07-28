
list(APPEND
PLASMA_EXAMPLES
cfar
# dummy_target
# pulse_doppler
)

# add_executable(dummy_target dummy_target.cpp)
# target_link_libraries(dummy_target PUBLIC plasma_dsp)
# target_include_directories(dummy_target PUBLIC ${CMAKE_SOURCE_DIR}/include)

# add_executable(pulse_doppler pulse_doppler_processing.cc)
# target_link_libraries(pulse_doppler PUBLIC plasma_dsp)
add_executable(cfar cfarTest.cc)
target_link_libraries(cfar PUBLIC plasma_dsp)
install(TARGETS ${PLASMA_EXAMPLES} DESTINATION ${PLASMA_EXAMPLE_DIR})