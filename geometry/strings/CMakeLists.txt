# Creates $<TARGET_OBJECTS:google-strings>
set(STRINGS_PUBLIC_H
    ascii_ctype.h
    split.h
    stringprintf.h
    strutil.h
    ../util/hash/hash_jenkins_lookup2.h
    )

set(STRINGS_SOURCES
    ${STRINGS_PUBLIC_H}
    ascii_ctype.cc
    split.cc
    stringprintf.cc
    strutil.cc
    )

add_library(google-strings
    OBJECT
    ${STRINGS_SOURCES}
    )