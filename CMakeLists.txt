cmake_minimum_required(VERSION 3.16)
project(MyApp)

# Définit le standard C++ et active la compilation avec des fonctionnalités de C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Chemin vers le répertoire source
set(APP_SOURCE_DIR ${CMAKE_SOURCE_DIR})

# Inclure GLFW et Walnut
add_subdirectory(${APP_SOURCE_DIR}/vendor/GLFW)

# Ajouter les fichiers source
file(GLOB_RECURSE SOURCES src/*.cpp)

# Ajouter l'exécutable
add_executable(${PROJECT_NAME} ${SOURCES} main.cpp
        Lumina/Application.h
        Lumina/Application.cpp)

# Ajouter les options pour une application console
set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE OFF)

# Trouver et inclure OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL glfw)

# Trouver et inclure Vulkan
find_package(Vulkan REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${Vulkan_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)

# Ajouter ImGui
set(IMGUI_DIR ${APP_SOURCE_DIR}/vendor/imgui)
file(GLOB IMGUI_SOURCES
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/imgui_demo.cpp # Assure-toi que ce fichier est inclus
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_vulkan.cpp
)
target_sources(${PROJECT_NAME} PRIVATE ${IMGUI_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${IMGUI_DIR} ${IMGUI_DIR}/backends)

# Liens avec les bibliothèques GLFW et Vulkan
target_link_libraries(${PROJECT_NAME} glfw Vulkan::Vulkan)
