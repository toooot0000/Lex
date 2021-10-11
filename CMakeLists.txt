cmake_minimum_required(VERSION 3.0.0)
project(Lex VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(/usr/local/include)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BASE_NAME test)
set(LEX_SUFFIX .l)
set(YACC_SUFFIX .y)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(PARSER_DIR ${SRC_DIR}/parser)


# Parser
set(REFLEX_PREFIX /usr/local/Cellar/re-flex)
set(REFLEX_VERSION 3.0.11)
set(REFLEX_SOURCE ${BASE_NAME}${LEX_SUFFIX})
set(BISON_SOURCE ${BASE_NAME}${YACC_SUFFIX})

include_directories(${REFLEX_PREFIX}/${REFLEX_VERSION}/include)

# Find re-flex
find_library(Reflex
    NAMES libreflex
    REQUIRED
)
message("Reflex = " ${Reflex})

# set a higher level bison
message("REFLEX_SOURCE = " ${REFLEX_SOURCE})
message("BISON_SOURCE = " ${BISON_SOURCE})

execute_process(
    COMMAND "reflex" ${REFLEX_SOURCE}
    COMMAND "bison" ${BISON_SOURCE}
    WORKING_DIRECTORY ${PARSER_DIR}
)

# Main part
FILE(GLOB SRC_FILES "${SRC_DIR}/**/*.cpp" "${SRC_DIR}/*.cpp")
message(${SRC_FILES})
add_executable(Lex ${SRC_FILES})


# Link Reflex
target_link_libraries(Lex PRIVATE ${Reflex})


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)




