cmake_minimum_required(VERSION 3.20)
project(codemorph
    VERSION 2.0.0
    LANGUAGES CXX
    DESCRIPTION "Encoding utilities library (BCD, ASCII, EBCDIC)"
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Options with CODEMORPH_ prefix for FetchContent compatibility
option(CODEMORPH_ENABLE_TESTING "Enable unit tests" ON)
option(CODEMORPH_ENABLE_WARNINGS "Enable compiler warnings" ON)
option(CODEMORPH_ENABLE_WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)

add_library(codemorph STATIC codemorph.cpp)
add_library(codemorph::codemorph ALIAS codemorph)

target_include_directories(codemorph
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(codemorph PUBLIC cxx_std_23)

include(cmake/Warnings.cmake)
codemorph_set_warnings(codemorph ${CODEMORPH_ENABLE_WARNINGS} ${CODEMORPH_ENABLE_WARNINGS_AS_ERRORS})

# Keep dependency builds independent of the parent project's testing options.
if(CODEMORPH_ENABLE_TESTING AND (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR))
    find_package(Catch2 3 REQUIRED)
    enable_testing()
    add_subdirectory(tests)
endif()

# Installation
include(GNUInstallDirs)
install(TARGETS codemorph
    EXPORT codemorph-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(FILES include/codemorph/codemorph.hpp DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/codemorph)
install(EXPORT codemorph-targets
    FILE codemorph-config.cmake
    NAMESPACE codemorph::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/codemorph
)
