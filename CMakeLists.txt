cmake_minimum_required(VERSION 2.8)
project(BrainActivityVisualizer C CXX)

find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL REQUIRED)
find_package(OpenGL REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 -Wall -Wextra -fexceptions")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

set(QT_USE_QTOPENGL TRUE)

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(build)
include_directories(inc/core)
include_directories(inc/gui)

file(GLOB core_src src/core/*.cpp)
file(GLOB gui_src src/gui/*.cpp)
file(GLOB gui_inc inc/gui/*.h)
file(GLOB forms forms/*.ui) 
file(GLOB resources resources/*.qrc)

QT4_WRAP_UI(forms_headers ${forms})
QT4_WRAP_CPP(gui_inc_moc ${gui_inc})
QT4_ADD_RESOURCES(resources_rcc ${resources})

ADD_EXECUTABLE(bac ${core_src} ${gui_src} ${gui_inc_moc} ${forms_headers} ${resources_rcc})
TARGET_LINK_LIBRARIES(bac ${QT_LIBRARIES} ${OPENGL_LIBRARIES})