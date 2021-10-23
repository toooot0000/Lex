cmake_minimum_required(VERSION 3.1.0)
project(Lex VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)

add_subdirectory(${SRC_DIR}/parser)

option(ENABLE_TEST "Enable testing?(T/F)" TRUE)
if(ENABLE_TEST)
    add_subdirectory(${TEST_DIR})
else(ENABLE_TEST)
    add_executable(Lex ${SRC_DIR}/main.cpp)
    target_link_libraries(Lex 
        PRIVATE Parser
    )
endif(ENABLE_TEST)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
