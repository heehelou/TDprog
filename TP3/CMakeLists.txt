cmake_minimum_required(VERSION 3.20)
project(TP3)

# Utilisation du C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Répertoire de sortie des exécutables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Création des exécutables pour chaque exercice
add_executable(ex1 ex1.cpp)
add_executable(ex2 ex2.cpp)
add_executable(ex3 ex3.cpp)
add_executable(ex4 ex4.cpp)
add_executable(ex5 ex5.cpp)

# Options de compilation pour des warnings utiles
if (MSVC)
    target_compile_options(ex1 PRIVATE /W3)
    target_compile_options(ex2 PRIVATE /W3)
    target_compile_options(ex3 PRIVATE /W3)
    target_compile_options(ex4 PRIVATE /W3)
    target_compile_options(ex5 PRIVATE /W3)
else()
    target_compile_options(ex1 PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(ex2 PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(ex3 PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(ex4 PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(ex5 PRIVATE -Wall -Wextra -Wpedantic)
endif()
