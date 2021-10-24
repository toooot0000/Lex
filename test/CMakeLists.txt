find_package(Catch2 2 REQUIRED)

add_executable(TestLexer test_main.cpp test_lexer.cpp)
target_include_directories(TestLexer PRIVATE ${CMAKE_SOURCE_DIR}/src/parser)
target_link_libraries(TestLexer Catch2::Catch2 Lexer)
# configure_file("./*.in" "./*.in" COPYONLY)

file(COPY ./
    DESTINATION ${CMAKE_BINARY_DIR}/test
    FILES_MATCHING PATTERN "*.in"
)
