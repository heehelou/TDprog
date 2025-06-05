# Nous voulons un cmake "récent" pour utiliser les dernières fonctionnalités
cmake_minimum_required(VERSION 3.24)

project(TP7_Graphs)

# Configuration pour C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optionel: Changer le dossier de sortie des exécutables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Créer les exécutables
add_executable(ex1 ex1.cpp)


# Configuration C++20 pour chaque exécutable
target_compile_features(ex1 PRIVATE cxx_std_20)


# Quelques options de compilation pour ajouter des warnings
if (MSVC)
    target_compile_options(ex1 PRIVATE /W3)

else()
    target_compile_options(ex1 PRIVATE -Wall -Wextra -Wpedantic)

endif()
