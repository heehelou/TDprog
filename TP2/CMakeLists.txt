# CMake minimum requis
cmake_minimum_required(VERSION 3.24)

# Nom du projet
project(TP2)

# Forcer l'utilisation de C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optionnel : Répertoire de sortie des exécutables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

# Ajoute tous les fichiers .cpp dans la racine du projet
file(GLOB SRC_FILES CONFIGURE_DEPENDS "*.cpp")

# Crée un exécutable pour chaque fichier source
foreach(SRC_FILE ${SRC_FILES})
    # On extrait le nom de l'exécutable sans extension
    get_filename_component(EXECUTABLE_NAME ${SRC_FILE} NAME_WE)

    # Crée un exécutable à partir du fichier source
    add_executable(${EXECUTABLE_NAME} ${SRC_FILE})

    # Assure que C++17 est utilisé pour chaque exécutable
    target_compile_features(${EXECUTABLE_NAME} PRIVATE cxx_std_17)

    # Ajoute des options de compilation
    if (MSVC)
        target_compile_options(${EXECUTABLE_NAME} PRIVATE /W3)
    else()
        target_compile_options(${EXECUTABLE_NAME} PRIVATE -Wall -Wextra -Wpedantic -pedantic-errors)
    endif()
endforeach()
