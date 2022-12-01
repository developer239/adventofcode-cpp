set(TEST_NAME Day1Test)

aux_source_directory(. TEST_FILES)

add_executable(${TEST_NAME} ${TEST_FILES})

target_link_libraries(${TEST_NAME} PRIVATE ${LIB_NAME})

#
# Include Google Test

target_link_libraries(${TEST_NAME} PRIVATE gtest gmock gmock_main)

add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
