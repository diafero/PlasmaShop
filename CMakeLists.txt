project(PlasmaShop)
cmake_minimum_required(VERSION 2.8.11.2)

set(CMAKE_AUTOMOC TRUE)

if(POLICY CMP0071)
    # Don't run generated source files (bytes/python_*.cpp) through automoc
    cmake_policy(SET CMP0071 OLD)
endif()

find_package(HSPlasma REQUIRED)
find_package(string_theory REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

add_definitions(-DST_NO_2_0_DEPRECATION)

if(MSVC)
    add_definitions("/D_CRT_SECURE_NO_WARNINGS")
    # Fix <windows.h> doing stupid stuff to QDateTime's header
    add_definitions("/DNOMINMAX")
endif()
add_subdirectory(QScintilla/Qt4Qt5)

if(WIN32)
    add_definitions(-DPLAT_FONT="Courier New")
else()
    add_definitions(-DPLAT_FONT="Monospace")
endif()

# do this after QScintilla - it generates tons of warnings
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX OR
        CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    set(WARNING_FLAGS "-Wall -Wextra")
    set(CMAKE_CXX_FLAGS "-std=c++0x ${WARNING_FLAGS} ${CMAKE_CXX_FLAGS}")
    set(CMAKE_C_FLAGS "${WARNING_FLAGS} ${CMAKE_C_FLAGS}")
endif()

# Get the version number from git
set(PlasmaShop_VERSION "3.0-untracked")
if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
    find_program(GIT_EXECUTABLE NAMES git git.cmd)
    mark_as_advanced(GIT_EXECUTABLE)
    if(GIT_EXECUTABLE)
        execute_process(COMMAND ${GIT_EXECUTABLE} describe --dirty
                        OUTPUT_VARIABLE PlasmaShop_VERSION
                        OUTPUT_STRIP_TRAILING_WHITESPACE
                        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
    endif()
endif()
add_definitions(-DPLASMASHOP_VERSION="${PlasmaShop_VERSION}")

include_directories(${STRING_THEORY_INCLUDE_DIRS})

add_subdirectory(src)

if(WIN32)
    add_subdirectory(icons/win32)
endif()
