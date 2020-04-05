cmake_minimum_required(VERSION 3.0.0)
project(eop VERSION 0.1.0)

include(CTest)
enable_testing()

add_library(eop INTERFACE)

target_include_directories(eop INTERFACE
                           "$<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}/eop>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

list(APPEND headers "${CMAKE_CURRENT_SOURCE_DIR}/include/eop/concepts.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/include/eop/intrinsics.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/include/eop/ch-01/founds.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/include/eop/ch-02/transorbs.hpp")
target_sources(eop INTERFACE "$<BUILD_INTERFACE:${headers}>"

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)