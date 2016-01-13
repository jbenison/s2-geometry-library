# Creates $<TARGET_OBJECTS:google-util-coding>
set(UTIL_CODING_PUBLIC_H
    coder.h
    varint.h
    )

set(UTIL_CODING_SOURCES
    ${UTIL_CODING_PUBLIC_H}
    coder.cc
    varint.cc
    )

add_library(google-util-coding
    OBJECT
    ${UTIL_CODING_SOURCES}
    )