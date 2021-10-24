
add_library(Lexer lexer.cpp)
target_compile_features(Lexer PUBLIC cxx_std_20)

add_library(Parser parser.cpp)
# target_link_libraries(Parser Lexer)