# Creates $<TARGET_OBJECTS:google-util-math>
set(UTIL_MATH_PUBLIC_H
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
    vector4-inl.h
    )

set(UTIL_MATH_SOURCES
    ${UTIL_MATH_PUBLIC_H}
    mathlimits.cc
    mathutil.cc
    exactfloat/exactfloat.cc
    )

add_library(google-util-math
    OBJECT
    ${UTIL_MATH_SOURCES}
    )