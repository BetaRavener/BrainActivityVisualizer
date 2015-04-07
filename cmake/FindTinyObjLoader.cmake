# Once done this will define
#
# TINYOBJLOADER_FOUND
# TINYOBJLOADER_INCLUDE_DIR
# TINYOBJLOADER_LIBRARY
# 

cmake_minimum_required( VERSION 2.8 )

set( TINYOBJLOADER_FOUND FALSE )

find_path(
	TINYOBJLOADER_INCLUDE_DIR
	tiny_obj_loader.h
	PATH_SUFFIXES
		include
	PATHS
		/usr
		/usr/local
		${TINYOBJLOADER_DIR}
)

find_library(
	TINYOBJLOADER_LIBRARY
	tinyobjloader
	PATH_SUFFIXES
		lib
		lib64
	PATHS
		/usr
		/usr/local
		${TINYOBJLOADER_DIR}
)

if( NOT TINYOBJLOADER_INCLUDE_DIR OR NOT TINYOBJLOADER_LIBRARY )
	message( FATAL_ERROR "TinyObjLoader not found.\nSet TINYOBJLOADER_DIR manually or\ndefine TINYOBJLOADER_INCLUDE_DIR and TINYOBJLOADER_LIBRARY." )
else()
	message( STATUS "TinyObjLoader found: ${TINYOBJLOADER_INCLUDE_DIR}" )
endif()