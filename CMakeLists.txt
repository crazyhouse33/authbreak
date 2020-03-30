if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
	message( FATAL_ERROR "In-source builds not allowed. Run cmake .. into the build directory. You need to remove CMakeFiles and CMakeCache.txt as it can not be done automatically inside the CMakeList. run:
	rm CMakeCache.txt
	rm -rf CMakeFiles	
	" )
	# Does not work
    file(REMOVE_RECURSE CMakeFiles)
    file(REMOVE CMakeCache.txt)
endif()

cmake_minimum_required(VERSION 3.7)

project(authbreak C )

set (version 0.0)

# Adding version to the code
add_definitions(-DAUTHBREAK_VERSION="${version}")

###### Separating test and normal build sources   #######
#maybe this whole concern about separating the sources / tests is useless, I am not strong enought in C, I am just trying to preserve namespace of the normal build.

#TODO manage the libs folders,

# Indicating headers are in source and lib normal 
#include_directories(src ext/normal/extern.h)

# Setting discovery source variables for latter compilation)
#TODO when the project is done, desactivate globbing and just copy past grep output
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.h src/*.c)
file(GLOB_RECURSE EXTERN_SOURCES CONFIGURE_DEPENDS extern/normal/src/*.h extern/normal/src/*.c)
file(GLOB_RECURSE EXTERN_SOURCES_TEST CONFIGURE_DEPENDS extern/test/src/*.h extern/test/src/*.c)
 
list (APPEND SOURCES ${EXTERN_SOURCES})


# Building main executable
add_subdirectory(src)

##### TEST 
enable_testing() 


message(TEST ${EXTERN_SOURCES_TEST})
list (APPEND SOURCES ${EXTERN_SOURCES_TEST})
# Building tests
add_subdirectory(tests)
