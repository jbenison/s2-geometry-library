set(INCLUDE_FILES
        mathlimits.h
        mathutil.h
        exactfloat/exactfloat.h
        matrix3x3.h
        matrix3x3-inl.h
        vector2.h
        vector2-inl.h
        vector3.h
        vector3-inl.h
        vector4.h
        vector4-inl.h)

set(SOURCE_FILES
        mathlimits.cc
        mathutil.cc
        exactfloat/exactfloat.cc)

add_library(google-util-math
        OBJECT
        ${INCLUDE_FILES}
        ${SOURCE_FILES})