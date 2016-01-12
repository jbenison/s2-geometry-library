# Creates libgoogle-base.a
set(INCLUDE_FILES
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
        stl_decl.h
        stl_decl_msvc.h
        stl_decl_osx.h
        stringprintf.h
        strtoint.h
        template_util.h
        type_traits.h)

set(SOURCE_FILES
        int128.cc
        logging.cc
        stringprintf.cc
        strtoint.cc)

add_library(google-base
        OBJECT
        ${INCLUDE_FILES}
        ${SOURCE_FILES})