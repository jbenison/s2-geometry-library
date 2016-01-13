# Builds the following libraries
# libs2.a
# libs2cellid.a

# Project won't build without these flags
# @TODO: Fix this.
add_definitions(-DNDEBUG)
# @TODO: Use MPFR?
add_definitions(-DS2_USE_EXACTFLOAT)

# Builds $<TARGET_OBJECTS:google-base>
add_subdirectory(base)

# Builds $<TARGET_OBJECTS:google-strings>
add_subdirectory(strings)

# Builds $<TARGET_OBJECTS:google-util-coding>
# and $<TARGET_OBJECTS:google-util-math>
add_subdirectory(util)

set(S2CELLID_PUBLIC_H
    s1angle.h
    s2.h
    s2cellid.h
    s2latlng.h
    )

set(S2CELLID_SOURCES
    ${S2CELLID_PUBLIC_H}
    s1angle.cc
    s2.cc
    s2cellid.cc
    s2latlng.cc
    )

add_library(s2cellid
    ${S2CELLID_SOURCES}
    $<TARGET_OBJECTS:google-base>
    $<TARGET_OBJECTS:google-strings>
    $<TARGET_OBJECTS:google-util-coding>
    $<TARGET_OBJECTS:google-util-math>
    )

target_include_directories(s2cellid
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    )

set(S2_PUBLIC_H
    r1interval.h
    s1interval.h
    s2cap.h
    s2cell.h
    s2cellunion.h
    s2edgeindex.h
    s2edgeutil.h
    s2latlngrect.h
    s2loop.h
    s2pointregion.h
    s2polygon.h
    s2polygonbuilder.h
    s2polyline.h
    s2r2rect.h
    s2region.h
    s2regioncoverer.h
    s2regionintersection.h
    s2regionunion.h
    )

set(S2_SOURCES
    ${S2_PUBLIC_H}
    s1interval.cc
    s2cap.cc
    s2cell.cc
    s2cellunion.cc
    s2edgeindex.cc
    s2edgeutil.cc
    s2latlngrect.cc
    s2loop.cc
    s2pointregion.cc
    s2polygon.cc
    s2polygonbuilder.cc
    s2polyline.cc
    s2r2rect.cc
    s2region.cc
    s2regioncoverer.cc
    s2regionintersection.cc
    s2regionunion.cc
    )

add_library(s2
    ${S2_SOURCES}
    $<TARGET_OBJECTS:google-base>
    $<TARGET_OBJECTS:google-strings>
    $<TARGET_OBJECTS:google-util-coding>
    $<TARGET_OBJECTS:google-util-math>
    )

target_include_directories(s2
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    )

# Install headers
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DESTINATION include/s2
    FILES_MATCHING PATTERN "*.h"
    )

# Install libs
install(TARGETS s2 s2cellid
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    )