set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/tests)
# Test discovery and building 
file(GLOB_RECURSE TESTS *.c)
foreach(file ${TESTS})
	message("${file} detected as a test")
  get_filename_component (name_without_extension ${file} NAME_WE)
  add_executable(${name_without_extension} ${SOURCES} ${file})
  add_test(NAME ${name_without_extension} COMMAND ${name_without_extension})
endforeach()


