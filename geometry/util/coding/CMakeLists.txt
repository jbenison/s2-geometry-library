
add_library(google-util-coding
        coder.cc
        varint.cc)

target_include_directories(google-util-coding PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})