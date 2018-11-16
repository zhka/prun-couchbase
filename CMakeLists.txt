cmake_minimum_required(VERSION 2.6)
set(TARGET prun-couchbase)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/libcouchbase-cxx/include)
set(CMAKE_CXX_FLAGS "-std=c++0x -Wall -Wextra -Wno-unused-parameter -Wno-long-long -pedantic -pthread -g -O3")

find_package(Boost REQUIRED COMPONENTS thread system)

set(REQUIRED_LIBRARIES
  ${Boost_LIBRARIES}
)

set(SOURCE
  ${PROJECT_SOURCE_DIR}/dbcouchbase.cpp
)

add_library(${TARGET} SHARED ${SOURCE})
target_link_libraries( ${TARGET} ${REQUIRED_LIBRARIES} couchbase -lrt -rdynamic )

install(TARGETS ${TARGET}
  LIBRARY DESTINATION lib${LIB_SUFFIX}
  BUNDLE DESTINATION library)
