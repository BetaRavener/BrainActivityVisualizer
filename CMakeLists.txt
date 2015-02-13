cmake_minimum_required(VERSION 2.8.11)
project(BrainActivityVisualizer C CXX)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 -Wall -Wextra")
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

add_executable(bac ${core_src} ${gui_src} ${gui_inc_moc} ${forms_headers} ${resources_rcc})
target_link_libraries(bac Qt5::Widgets Qt5::Core Qt5::Gui)

set(tinyobj_inc_dir CACHE PATH "")
if(NOT DEFINED tinyobj_inc_dir)
    message( FATAL_ERROR "Tinyobjloader include directory not set.")
endif()
if(NOT EXISTS ${tinyobj_inc_dir})
    message( FATAL_ERROR "Tinyobjloader include directory does not exists: ${tinyobj_inc_dir}")
endif()
if(NOT EXISTS ${tinyobj_inc_dir}/tiny_obj_loader.h)
    message( FATAL_ERROR "Tinyobjloader headers not found at specified path.")
endif()
    
set(tinyobj_lib_dir CACHE PATH "")
if(NOT DEFINED tinyobj_lib_dir)
    message( FATAL_ERROR "Tinyobjloader library directory not set.")
endif()
if(NOT EXISTS ${tinyobj_lib_dir})
    message( FATAL_ERROR "Tinyobjloader library directory does not exists: ${tinyobj_lib_dir}")
endif()
set(tinyobj_lib ${tinyobj_lib_dir}/tinyobjloader.lib)
if(NOT EXISTS ${tinyobj_lib})
    message( FATAL_ERROR "Tinyobjloader library not found at specified path.")
endif()

include_directories(${tinyobj_inc_dir})
# add imported target
add_library(imp_tinyobj STATIC IMPORTED)
# point the imported target at the real file
set_property(TARGET imp_tinyobj PROPERTY IMPORTED_LOCATION ${tinyobj_lib})
target_link_libraries(bac imp_tinyobj)