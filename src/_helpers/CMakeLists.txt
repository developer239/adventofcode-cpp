set(LIB_NAME Helpers)

add_library(${LIB_NAME} STATIC src/ReadInput.cpp src/LogVectorLines.cpp src/Tokenize.cpp src/SplitString.cpp)

target_include_directories(${LIB_NAME} INTERFACE .)
