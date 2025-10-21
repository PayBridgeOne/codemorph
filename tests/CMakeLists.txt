find_package(Catch2 3 REQUIRED)
add_executable(tests main.cpp
        bench_codemorph.cpp)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain CodeMorph)

include(Catch)
catch_discover_tests(tests) 