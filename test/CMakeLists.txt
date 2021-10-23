find_package(Catch2 2 REQUIRED)

# macro(add_catch_test TARGET MODULE_NAME)
#     add_executable("Test_${TARGET}" "test_${TARGET}.cpp")
#     target_include_directories("Test_${TARGET}" PRIVATE ${CMAKE_SOURCE_DIR}/src/${MODULE_NAME})
#     target_link_libraries("Test_${TARGET}" Catch2::Catch2 ${MODULE_NAME})
# endmacro(add_catch_test)

# add_catch_test(lexer parser)
# add_catch_test(parser parser)

# add_executable(TestParser test_parser.cpp)
# target_include_directories(TestParser PRIVATE ${CMAKE_SOURCE_DIR}/src/parser)
# target_link_libraries(TestParser Catch2::Catch2)

add_executable(TestLexer test_main.cpp test_lexer.cpp)
target_include_directories(TestLexer PRIVATE ${CMAKE_SOURCE_DIR}/src/parser)
target_link_libraries(TestLexer Catch2::Catch2 Lexer)
configure_file(test_lexer.in test_lexer.in COPYONLY)


# add_executable(TestMain test_main.cpp)
# target_link_libraries(TestMain TestLexer)