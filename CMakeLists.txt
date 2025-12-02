cmake_minimum_required(VERSION 3.22)

project(SYSC_2006 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# ---------- Lab 8 ----------
add_executable(lab8
        lab8/main.c
        lab8/array_list.c
        lab8/my_string.c
)
target_include_directories(lab8 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/lab8
)

# ---------- Lab 9 ----------
add_executable(lab9
        lab9/main.c
        lab9/polynomial.c
)
target_include_directories(lab9 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/lab9
)


#--------------Lab 10 ---------------------------
add_executable(lab10
        lab10/main.c
        lab10/singly_linked_list.c
)
target_include_directories(lab10 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/lab10
)


#--------------Lab 11 ---------------------------
add_executable(lab11
        lab11/main.c
        lab11/sl_list.c
)
target_include_directories(lab11 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/lab11
)

#--------------Lab 12 ---------------------------
add_executable(lab12
        lab12/main.c
        lab12/circular_queue.c
)
target_include_directories(lab12 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/lab12
)

#--------------Lab 13 ---------------------------
add_executable(lab13
        lab13/main.c
        lab13/dictionary.c
)
target_include_directories(lab13 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/lab13
)


# ---------- Assignment 2: test runner ----------
add_executable(a2_tests
        "assignment 2/main_tests.c"
        "assignment 2/a2_functions.c"
)
target_include_directories(a2_tests PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/assignment 2"
)

# ---------- Assignment 2: your own main ----------
add_executable(a2_main
        "assignment 2/main.c"
        "assignment 2/a2_functions.c"
)
target_include_directories(a2_main PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/assignment 2"
)
