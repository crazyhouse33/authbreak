set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/tests)
# Test discovery and building 
file(GLOB_RECURSE TESTS *.c)
list(FILTER TESTS EXCLUDE REGEX .*/ext-tests/.*)
foreach(file ${TESTS})
	message("${file} detected as a test")
  get_filename_component (name_without_extension ${file} NAME_WE)
  add_executable(${name_without_extension} ${SOURCES} ${file})
  add_test(NAME ${name_without_extension} COMMAND ${name_without_extension} WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})
endforeach()


file(GLOB_RECURSE EXT_TEST ext-tests/*.c)
foreach(file ${EXT_TEST})
	message ("${file} detected as necessary for tests")
	get_filename_component (name_without_extension ${file} NAME_WE)
  	add_executable(${name_without_extension} ${file})
endforeach()






