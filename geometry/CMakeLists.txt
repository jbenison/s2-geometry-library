
add_definitions(-DNDEBUG)
add_definitions(-DS2_USE_EXACTFLOAT)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(base)
add_subdirectory(strings)
add_subdirectory(util)

add_library(s2cellid
        s1angle.cc
        s2.cc
        s2cellid.cc
        s2latlng.cc)

target_include_directories(s2cellid PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(s2
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

target_include_directories(s2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
