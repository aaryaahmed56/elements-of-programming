cmake_minimum_required(VERSION 3.0.0)
project(eop VERSION 0.1.0)

include(CTest)
enable_testing()

add_library(eop INTERFACE)

target_include_directories(eop INTERFACE
                           "$<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}/src>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

list(APPEND headers "${CMAKE_CURRENT_SOURCE_DIR}/src/concepts.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/src/intrinsics.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/src/precomp.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/src/ch-01/founds.hpp")
target_sources(crh INTERFACE "$<BUILD_INTERFACE:${headers}>"

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
