# Creates $<TARGET_OBJECTS:google-base>
set(BASE_PUBLIC_H
    basictypes.h
    casts.h
    commandlineflags.h
    docid.h
    int128.h
    integral_types.h
    logging.h
    macros.h
    port.h
    scoped_ptr.h
    stringprintf.h
    strtoint.h
    template_util.h
    type_traits.h
    )

set(BASE_SOURCES
    ${BASE_PUBLIC_H}
    int128.cc
    logging.cc
    stringprintf.cc
    strtoint.cc
    )

add_library(google-base
    OBJECT
    ${BASE_SOURCES}
    )