cmake_minimum_required(VERSION 3.19)
project(AdventOfCode LANGUAGES CXX VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_subdirectory(externals/googletest)
enable_testing()

# create function called "initialize_libray" that takes single argument
function(initialize_library library_name library_folder)
    set(APP_NAME ${library_name})
    set(APP_NAME_TEST ${library_name}Test)
    set(APP_FOLDER_NAME ${library_folder})

    set(SOURCES main.cpp)

    add_executable(${APP_NAME} ${SOURCES})
    add_test(AllTests${APP_NAME} ${APP_NAME})

    file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/src/2021/${APP_FOLDER_NAME})
    file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/src/2022/${APP_FOLDER_NAME})
    file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/src/2023/${APP_FOLDER_NAME})

    target_link_libraries(${APP_NAME} PRIVATE Helpers)

    # Tests

    set(SOURCES_TEST test.cpp)
    add_executable(${APP_NAME_TEST} ${SOURCES_TEST})
    target_link_libraries(${APP_NAME_TEST} PRIVATE gtest gmock gmock_main Helpers)
endfunction()

add_subdirectory(src)
