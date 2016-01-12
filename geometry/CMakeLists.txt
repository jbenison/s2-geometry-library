# Builds the following libraries
# libs2.a
# libs2cellid.a

# Project won't build without these flags
add_definitions(-DNDEBUG)
add_definitions(-DS2_USE_EXACTFLOAT)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(base)
add_subdirectory(strings)
add_subdirectory(util)

set(S2CELLID_INCLUDE_FILES
        s1angle.h
        s2.h
        s2cellid.h
        s2latlng.h)

set(S2CELLID_SOURCE_FILES
        s1angle.cc
        s2.cc
        s2cellid.cc
        s2latlng.cc)

add_library(s2cellid
        ${S2CELLID_INCLUDE_FILES}
        ${S2CELLID_SOURCE_FILES}
        $<TARGET_OBJECTS:google-base>
        $<TARGET_OBJECTS:google-strings>
        $<TARGET_OBJECTS:google-util-coding>
        $<TARGET_OBJECTS:google-util-math>)

target_include_directories(s2cellid PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set(S2_INCLUDE_FILES
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
        s2regionunion.h)

set(S2_SOURCE_FILES
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
        s2regionunion.cc)

add_library(s2
        ${S2_INCLUDE_FILES}
        ${S2_SOURCE_FILES}
        $<TARGET_OBJECTS:google-base>
        $<TARGET_OBJECTS:google-strings>
        $<TARGET_OBJECTS:google-util-coding>
        $<TARGET_OBJECTS:google-util-math>)

target_include_directories(s2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
