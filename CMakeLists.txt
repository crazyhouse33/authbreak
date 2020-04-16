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
include(.cmakefunc)

project(authbreak C )

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG "-ggdb3")
set (version 0.0)
include(.cmakedependencies_set_up) # Finding necessary standard libs


# Adding version to the code
add_definitions(-DAUTHBREAK_VERSION="${version}")
add_definitions(-DSTDBUFLIBPATH="${libstdbuf}")
###### Separating test and normal build sources   #######
#maybe this whole concern about separating the sources / tests is useless, I am not strong enought in C, I am just trying to preserve namespace of the normal build.

#TODO manage the libs folders,

# Setup Include dirs (This is a good argument to say Cmake sucks. Now seriously I dont know if there is better tool yet but I will check for another one next time. Seriously whatever the litle thing you want to do feel like fighting to death)

#TODO create a function / macro

include_subdirectories(src)
include_subdirectories(extern/normal/src)


# Setting discovery source variables for latter compilation)
#TODO when the project is done, desactivate globbing and just copy past grep output
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.h src/*.c)
file(GLOB_RECURSE EXTERN_SOURCES CONFIGURE_DEPENDS extern/normal/src/*.h extern/normal/src/*.c)
file(GLOB_RECURSE EXTERN_SOURCES_TEST CONFIGURE_DEPENDS extern/test/src/*.h extern/test/src/*.c)

JOIN(";${SOURCES}" \n\t pretty)
message ("\nDetected internal sources in src:\n${pretty} ")

JOIN(";${EXTERN_SOURCES}" \n\t pretty)
message ("\nDetected external sources in extern/normal/src:\n${pretty}")

JOIN(";${EXTERN_SOURCES_TEST}" \n\t pretty)
message ("\nDetected sources  for test build in extern/test/src:\n ${pretty}")
 

# Removing garbage among external sources
list (REMOVE_ITEM EXTERN_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/extern/normal/src/munit/example.c )
list (APPEND SOURCES ${EXTERN_SOURCES})


# Building main executable
add_subdirectory(src)

##### TEST 
enable_testing() 

# Removing the normal entry point 
list (REMOVE_ITEM SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c )


# Adding test related extern sources
include_subdirectories(extern/test/src)
list (APPEND SOURCES ${EXTERN_SOURCES_TEST})
# Building tests
add_subdirectory(tests)
