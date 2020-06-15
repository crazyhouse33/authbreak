# Protection to not mess up sources
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

#Common use functions
include(build-helpers/cmakefunc)

#Setting compilation options
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG "-ggdb3")
set (version 0.5)
#allow C programs to get the version
add_definitions(-DAUTHBREAK_VERSION="${version}")
include(build-helpers/cmake_dependencies_set_up) # Finding necessary standard libs and seting up path in the code


#TODO put it separate file
#if we are not in master, we need to us templates to fill some files for master
set ( CONFIGURE_DIR ${CMAKE_SOURCE_DIR}/dev/push_release_to_master)
if(EXISTS "${CONFIGURE_DIR}")
configure_file(${CONFIGURE_DIR}/push_to_master.py.cmake_template ${CONFIGURE_DIR}/push_to_master.py)#give python version number

configure_file(${CONFIGURE_DIR}/README.md.cmake_template ${CMAKE_SOURCE_DIR}/README.md)#give readme version number

endif()

###### Separating test and normal build sources   #######

#TODO manage the libs folders,

# Setup Include dirs 
include_subdirectories(src)
include_subdirectories(extern/normal/src)


# Setting discovery source variables for latter compilation)
#TODO when the project is done, desactivate globbing and just copy past grep output
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.h src/*.c)
file(GLOB_RECURSE EXTERN_SOURCES CONFIGURE_DEPENDS extern/normal/src/*.h extern/normal/src/*.c)
file(GLOB_RECURSE EXTERN_SOURCES_TEST CONFIGURE_DEPENDS extern/test/src/*.h extern/test/src/*.c)
file(GLOB_RECURSE TESTS_SOURCES ${PROJECT_SOURCE_DIR}/tests/shared-codebase/*.c ${PROJECT_SOURCE_DIR}/tests/shared-codebase/*.h)

#pretty printing sources for debuging build process
JOIN(";${SOURCES}" \n\t pretty)
message ("\nDetected internal sources in src:\n${pretty} ")

JOIN(";${EXTERN_SOURCES}" \n\t pretty)
message ("\nDetected external sources in extern/normal/src:\n${pretty}")

JOIN(";${TESTS_SOURCES}" \n\t pretty)
message ("\nDetected sources for test build in test/shared-codebase:\n ${pretty}")

JOIN(";${EXTERN_SOURCES_TEST}" \n\t pretty)
message ("\nDetected sources external sources for test build in extern/test/src:\n ${pretty}")
 

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
include_subdirectories(tests/shared-codebase)

list(APPEND SOURCES ${TESTS_SOURCES})
list (APPEND SOURCES ${EXTERN_SOURCES_TEST})
# Building tests
add_subdirectory(tests)

#Adittional targets
include(build-helpers/cmake_lazy_testing_targets) # need to be after test discovery
