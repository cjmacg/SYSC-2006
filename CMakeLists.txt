cmake_minimum_required(VERSION 3.22)
project(Coding C)
set(CMAKE_C_STANDARD 11)

# ---------- Lab 8 ----------
add_executable(lab8
        lab8/main.c
        lab8/array_list.c
        lab8/my_string.c
)
target_include_directories(lab8 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lab8)

# ---------- Lab 9 ----------
add_executable(lab9
        lab9/main.c
        lab9/polynomial.c
)
target_include_directories(lab9 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lab9)
