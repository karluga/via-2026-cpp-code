cmake_minimum_required(VERSION 3.16)
project(SystemMonitor CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find GLFW library
find_package(glfw3 CONFIG QUIET)
if(NOT glfw3_FOUND)
    find_package(glfw3 QUIET)
endif()

set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

set(APP_SOURCES
    src/main.cpp
    src/SystemInfo.cpp
    src/Dashboard.cpp
)

add_executable(SystemMonitor ${APP_SOURCES} ${IMGUI_SOURCES})

target_include_directories(SystemMonitor PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

# Static linking options for Windows / MinGW to create a standalone .exe
if(WIN32)
    target_compile_definitions(SystemMonitor PRIVATE GLFW_STATIC)
    if(MINGW)
        target_link_options(SystemMonitor PRIVATE -static -static-libgcc -static-libstdc++)
    endif()
endif()

# Try finding static GLFW library first for standalone binary
find_library(GLFW_STATIC_LIB NAMES libglfw3.a glfw3)

if(GLFW_STATIC_LIB)
    target_link_libraries(SystemMonitor PRIVATE ${GLFW_STATIC_LIB})
elseif(TARGET glfw)
    target_link_libraries(SystemMonitor PRIVATE glfw)
elseif(TARGET glfw3)
    target_link_libraries(SystemMonitor PRIVATE glfw3)
else()
    target_link_libraries(SystemMonitor PRIVATE glfw3)
endif()

if(WIN32)
    target_link_libraries(SystemMonitor PRIVATE opengl32 gdi32 user32 shell32 dwmapi ntdll psapi)
endif()
