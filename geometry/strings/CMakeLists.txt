# Creates libgoogle-strings.a
set(SOURCE_FILES
        ascii_ctype.cc
        split.cc
        stringprintf.cc
        strutil.cc
        ../util/hash/hash_jenkins_lookup2.h)

set(INCLUDE_FILES
        ascii_ctype.h
        split.h
        stringprintf.h
        strutil.h)

add_library(google-strings
        OBJECT
        ${INCLUDE_FILES}
        ${SOURCE_FILES})