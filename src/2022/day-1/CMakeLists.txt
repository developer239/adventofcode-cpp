set(APP_NAME Day1)
set(APP_NAME_TEST Day1Test)
set(APP_FOLDER_NAME day-1)

set(SOURCES main.cpp)

add_executable(${APP_NAME} ${SOURCES})

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/src/2022/${APP_FOLDER_NAME})

target_link_libraries(${APP_NAME} PRIVATE Helpers)

# Tests

set(SOURCES_TEST test.cpp)
add_executable(${APP_NAME_TEST} ${SOURCES_TEST})
target_link_libraries(${APP_NAME_TEST} PRIVATE gtest gmock gmock_main Helpers)
