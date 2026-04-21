cmake_minimum_required(VERSION 3.16)

project(ArithmeticTokenizer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Backend library
add_library(calculator_backend
    src/backend/tokenizer.cpp
    src/backend/parser.cpp
    src/backend/evaluator.cpp
    src/backend/calculator_engine.cpp
    src/backend/error_handler.cpp
    src/backend/history_manager.cpp
)

target_include_directories(calculator_backend PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# Console app for testing
add_executable(calculator_app
    src/main.cpp
)

target_link_libraries(calculator_app PRIVATE
    calculator_backend
)