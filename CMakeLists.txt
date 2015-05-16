cmake_minimum_required(VERSION 2.8.11)
project(BrainActivityVisualizer C CXX)

# Set some Win32 Specific Settings
IF(WIN32)
SET(GUI_TYPE WIN32)
ENDIF(WIN32)
# Set some Apple MacOS Specific settings
IF (APPLE)
SET(GUI_TYPE MACOSX_BUNDLE)
ENDIF (APPLE)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Set path to cmake modules (find)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)
find_package(TinyObjLoader REQUIRED)
find_package(UniShader REQUIRED)
find_package(GLM REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 -Wall -Wextra -Wno-comment -Wuninitialized")
add_definitions("-D_LARGEFILE64_SOURCE -D_LARGEFILE_SOURCE -DGLEW_MX")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

#INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

include_directories(inc/core)
include_directories(inc/signal)
include_directories(inc/gui)

file(GLOB core_src src/core/*.cpp)
file(GLOB core_inc inc/core/*.h)
file(GLOB signal_src src/signal/*.cpp)
file(GLOB signal_inc inc/signal/*.h)
file(GLOB gui_src src/gui/*.cpp)
file(GLOB gui_inc inc/gui/*.h)
file(GLOB forms forms/*.ui) 
file(GLOB resources resources/*.qrc)

QT5_WRAP_UI(forms_headers ${forms})
QT5_WRAP_CPP(gui_inc_moc ${gui_inc})
QT5_ADD_RESOURCES(resources_rcc ${resources})

add_executable(bav ${GUI_TYPE} ${core_src} ${signal_src} ${gui_src} ${gui_inc_moc} ${forms_headers} ${resources_rcc})
if (DEVEL_PROJ)
    add_custom_target(dummy_headers SOURCES ${core_inc} ${signal_inc} ${gui_inc})
endif()
target_link_libraries(bav Qt5::Widgets Qt5::Core Qt5::Gui)

include_directories(${TINYOBJLOADER_INCLUDE_DIR})
# add imported target
add_library(imp_tinyobj STATIC IMPORTED)
# point the imported target at the real file
set_property(TARGET imp_tinyobj PROPERTY IMPORTED_LOCATION ${TINYOBJLOADER_LIBRARY})
target_link_libraries(bav imp_tinyobj)

include_directories(${UNISHADER_INCLUDE_DIR})
target_link_libraries(bav ${UNISHADER_LIBRARY})

include_directories(${GLM_INCLUDE_DIR})

include_directories(${GLEW_INCLUDE_PATH})
target_link_libraries(bav ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLEW_LIBRARY})

if (TEST_PROJ)
    file(GLOB test_src src/test/*.cpp)
    add_executable(sigTest ${signal_src} ${test_src})
endif()