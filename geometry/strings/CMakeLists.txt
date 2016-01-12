
add_library(google-strings
        ascii_ctype.cc
        split.cc
        stringprintf.cc
        strutil.cc)

target_include_directories(google-strings PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})