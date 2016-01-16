# Builds the following libraries
# libs2.a
# libs2cellid.a

# @TODO: Use MPFR?
add_definitions(-DS2_USE_EXACTFLOAT)
# @TODO: Use std::hash, std::unordered_map
add_definitions(-DHASH_NAMESPACE=__gcc_cxx)

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

if(BUILD_TESTING)
  include_directories(${GTEST_INCLUDE_DIR})

  set(TEST_SOURCES
      s2testing.h
      s2testing.cc
      s2main_test.cc
      )

  set(TEST_TARGETS
      r1interval_test
      s1angle_test
      s1interval_test
      s2_test
      s2cap_test
      s2cell_test
      s2cellid_test
      s2cellunion_test
      s2edgeindex_test
      s2edgeutil_test
      s2latlng_test
      s2latlngrect_test
      s2loop_test
      s2pointregion_test
      s2polygon_test
      s2polygonbuilder_test
      s2polyline_test
      s2r2rect_test
      s2regioncoverer_test
      s2regionunion_test
      )

  foreach(target ${TEST_TARGETS})
    add_executable(${target} ${target}.cc ${TEST_SOURCES})
    target_link_libraries(${target} s2 s2cellid ${LIBS} ${GTEST_LIBRARY})
    add_test(NAME ${target} COMMAND ${target})
  endforeach(target)

endif(BUILD_TESTING)

if(BUILD_BENCHMARKS)
  include_directories(${BENCHMARK_INCLUDE_DIR})

  set(BENCHMARK_SOURCES
      s2testing.h
      s2testing.cc
      )

  set(BENCHMARK_TARGETS
      s2edgeindex_benchmark
      s2edgeutil_benchmark
      s2latlng_benchmark
      s2loop_benchmark
      s2polygon_benchmark
      s2regioncoverer_benchmark
      )

  foreach(target ${BENCHMARK_TARGETS})
    add_executable(${target} ${target}.cc ${BENCHMARK_SOURCES})
    target_link_libraries(${target} s2 s2cellid ${LIBS} ${BENCHMARK_LIBRARY})
  endforeach(target)

endif(BUILD_BENCHMARKS)

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