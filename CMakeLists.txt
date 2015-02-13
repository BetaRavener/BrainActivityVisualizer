cmake_minimum_required(VERSION 2.8.11)
project(BrainActivityVisualizer C CXX)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)
#find_package(OpenGL REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 -Wall -Wextra -fexceptions")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

#INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

include_directories(inc/core)
include_directories(inc/gui)

file(GLOB core_src src/core/*.cpp)
file(GLOB gui_src src/gui/*.cpp)
file(GLOB gui_inc inc/gui/*.h)
file(GLOB forms forms/*.ui) 
file(GLOB resources resources/*.qrc)

QT5_WRAP_UI(forms_headers ${forms})
QT5_WRAP_CPP(gui_inc_moc ${gui_inc})
QT5_ADD_RESOURCES(resources_rcc ${resources})

ADD_EXECUTABLE(bac ${core_src} ${gui_src} ${gui_inc_moc} ${forms_headers} ${resources_rcc})
TARGET_LINK_LIBRARIES(bac Qt5::Widgets Qt5::Core Qt5::Gui)