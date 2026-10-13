add_executable(codemorph_tests
    main.cpp
    bench_codemorph.cpp
)

target_link_libraries(codemorph_tests PRIVATE Catch2::Catch2WithMain codemorph::codemorph)
codemorph_set_warnings(codemorph_tests ${CODEMORPH_ENABLE_WARNINGS} ${CODEMORPH_ENABLE_WARNINGS_AS_ERRORS})

include(Catch)
catch_discover_tests(codemorph_tests)
