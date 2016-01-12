
add_library(google-util-math
        mathlimits.cc
        mathutil.cc
        exactfloat/exactfloat.cc)

target_include_directories(google-util-math PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})