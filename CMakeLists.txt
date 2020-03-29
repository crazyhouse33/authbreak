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


include_directories(src)

add_subdirectory(src)
#add_subdirectory(tests)
