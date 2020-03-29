#set(CMAKE_BUILD_TYPE RelWithDebInfo)
set(CMAKE_BUILD_TYPE Debug)
add_compile_options(-Wall -Wextra -pedantic -Wno-missing-field-initializers)
file(GLOB_RECURSE SOURCES *.h *.c)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

