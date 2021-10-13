set(BASE_NAME test)
set(LEX_SUFFIX .l)
set(YACC_SUFFIX .y)
set(REFLEX_SOURCE ${BASE_NAME}${LEX_SUFFIX})
set(BISON_SOURCE ${BASE_NAME}${YACC_SUFFIX})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

execute_process(
    COMMAND "reflex" ${REFLEX_SOURCE}
    COMMAND "bison" ${BISON_SOURCE}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

FILE(GLOB SRC_FILES "*.cpp")

add_library(Parser ${SRC_FILES})