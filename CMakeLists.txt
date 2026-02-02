cmake_minimum_required(VERSION 3.20)
project(CodeMorph
    VERSION 1.0.0
    LANGUAGES CXX
    DESCRIPTION "Encoding utilities library (BCD, ASCII, EBCDIC)"
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Options with CODEMORPH_ prefix for FetchContent compatibility
option(CODEMORPH_ENABLE_TESTING "Enable unit tests" ON)
option(CODEMORPH_ENABLE_WARNINGS "Enable compiler warnings" ON)
option(CODEMORPH_ENABLE_WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)

# Support legacy option names (for backwards compatibility)
if(DEFINED ENABLE_TESTING AND NOT ENABLE_TESTING)
    set(CODEMORPH_ENABLE_TESTING OFF)
endif()

add_library(codemorph STATIC codemorph.cpp)
add_library(codemorph::codemorph ALIAS codemorph)

# Also create legacy target name for backwards compatibility
add_library(CodeMorph ALIAS codemorph)

target_include_directories(codemorph
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(codemorph PUBLIC cxx_std_23)

# Tests (only if this is the main project or explicitly enabled)
if(CODEMORPH_ENABLE_TESTING AND (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR))
    find_package(Catch2 3 QUIET)
    if(Catch2_FOUND)
        include(CTest)
        enable_testing()
        add_subdirectory(tests)
    else()
        message(STATUS "CodeMorph: Catch2 not found, skipping tests")
    endif()
endif()

# Installation
include(GNUInstallDirs)
install(TARGETS codemorph
    EXPORT codemorph-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(FILES codemorph.hpp DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT codemorph-targets
    FILE codemorphConfig.cmake
    NAMESPACE codemorph::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/codemorph
)