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
# FetchContent pour les bibliothèques externes
# -------------------------------------------------------
include(FetchContent)

# --- spdlog ---
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.16.0
  )
FetchContent_MakeAvailable(spdlog)

# --- BNFParserLib ---
FetchContent_Declare(
    BNFParserLib
    GIT_REPOSITORY https://github.com/EvenZeppa/BNFParserLib.git
    GIT_TAG main
)
FetchContent_MakeAvailable(BNFParserLib)

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
target_include_directories(${PROJECT_NAME} PRIVATE
    ${spdlog_SOURCE_DIR}/include
    ${BNFParserLib_SOURCE_DIR}/include
)

# -------------------------------------------------------
# Lien avec les bibliothèques externes
# -------------------------------------------------------
target_link_libraries(${PROJECT_NAME} PRIVATE
    spdlog::spdlog
    bnf
)

# -------------------------------------------------------
# Mode Debug par défaut (utile pendant ft_irc)
# -------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()
