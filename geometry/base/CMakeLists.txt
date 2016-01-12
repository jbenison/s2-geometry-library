
add_library(google-base
        int128.cc
        logging.cc
        stringprintf.cc
        strtoint.cc)

target_include_directories(google-base PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})