cmake_minimum_required(VERSION 3.14)
project(ircserv LANGUAGES CXX)

# -------------------------------------------------------
# Configuration du compilateur
# -------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Flags proches de ton Makefile mais modernes
add_compile_options(-Wall -Wextra -Werror)

# -------------------------------------------------------
# Gestion des dépendances externes
# -------------------------------------------------------
set(DEPS_INSTALL_DIR ${CMAKE_BINARY_DIR}/deps)
file(MAKE_DIRECTORY ${DEPS_INSTALL_DIR})

include(ExternalProject)

# ---- spdlog ----
ExternalProject_Add(
    spdlog_ext
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.12.0
    PREFIX ${DEPS_INSTALL_DIR}/spdlog
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEPS_INSTALL_DIR}/spdlog/install
)

# ---- BNFParserLib ----
ExternalProject_Add(
    BNFParserLib_ext
    GIT_REPOSITORY https://github.com/EvenZeppa/BNFParserLib.git
    GIT_TAG main
    PREFIX ${DEPS_INSTALL_DIR}/BNFParserLib
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEPS_INSTALL_DIR}/BNFParserLib/install
)

# -------------------------------------------------------
# Arborescence du projet
# -------------------------------------------------------

# Tous les .cpp dans src/ récursivement
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    src/*.cpp
)

# Tous les headers dans include/
include_directories(include)

# -------------------------------------------------------
# Création de l’exécutable
# -------------------------------------------------------
add_executable(${PROJECT_NAME} ${SRC_FILES})

# -------------------------------------------------------
# Inclusion des headers des libs externes
# -------------------------------------------------------
target_include_directories(ircserv PRIVATE
    ${DEPS_INSTALL_DIR}/spdlog/install/include
    ${DEPS_INSTALL_DIR}/BNFParserLib/install/include
)

target_link_libraries(ircserv PRIVATE
    ${DEPS_INSTALL_DIR}/spdlog/install/lib/libspdlog.a
    ${DEPS_INSTALL_DIR}/BNFParserLib/install/lib/libbnf.a
)
