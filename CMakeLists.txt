cmake_minimum_required(VERSION 3.0.0)
project(Lex VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(/usr/local/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

add_executable(Lex ${SRC_DIR}/main.cpp)

add_subdirectory(${SRC_DIR}/Parser)
target_link_libraries(Lex 
    PRIVATE Parser
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)




