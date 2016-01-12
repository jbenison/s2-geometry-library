set(INCLUDE_FILES
        coder.h
        varint.h)

set(SOURCE_FILES
        coder.cc
        varint.cc)

add_library(google-util-coding
        OBJECT
        ${INCLUDE_FILES}
        ${SOURCE_FILES})