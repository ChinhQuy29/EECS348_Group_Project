# 1. Add the engine source files to the target
add_library(Calculatorz_FrontEnd SHARED
    calculator_frontend.cpp
    "../src/backend/calculator_engine.cpp"
    "../src/backend/parser.cpp"
    "../src/backend/evaluator.cpp"
    "../src/backend/tokenizer.cpp"
)

# 2. Make sure the compiler can find calculator_engine.hpp
target_include_directories(Calculatorz_FrontEnd PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/../include"
)