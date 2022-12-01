set(LIB_NAME Day1)

aux_source_directory(. SRC_FILES)

add_executable(${LIB_NAME} ${SRC_FILES})

target_include_directories(${LIB_NAME} INTERFACE .)

target_link_libraries(${LIB_NAME} PRIVATE gtest gmock gmock_main)

add_test(NAME ${LIB_NAME} COMMAND ${LIB_NAME})
