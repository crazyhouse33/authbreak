#putting test in bin/test
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/test_binaries)

set(list_lazy_tests )
set(list_mandatory_tests )








message("Test discovery and building:\n")
file(GLOB_RECURSE TESTS ${PROJECT_SOURCE_DIR}/tests/*.c)
list(FILTER TESTS EXCLUDE REGEX ${PROJECT_SOURCE_DIR}/tests/ext-tests/.*) # every .c in test excecpt the one in ext-test is to be compiled as a test
list(FILTER TESTS EXCLUDE REGEX ${PROJECT_SOURCE_DIR}/tests/shared-codebase/.*) #Those are not to compile
foreach(file ${TESTS})
  get_filename_component (name_without_extension ${file} NAME_WE)
  add_executable(${name_without_extension} ${SOURCES} ${file})
  target_link_libraries(${name_without_extension} eprof)
  add_test(NAME ${name_without_extension} COMMAND ${name_without_extension} WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})
  if (file MATCHES ${PROJECT_SOURCE_DIR}/tests/lazy/*)

	  message("\t${file} detected as a lazy test")
	  #listing test->executable test for the python script to let him check modification date of exe
	  list(APPEND list_lazy_tests "${name_without_extension} ${EXECUTABLE_OUTPUT_PATH}/${name_without_extension}")
  else()
	message("\t${file} detected as a mandatory test")
	  list(APPEND list_mandatory_tests "${name_without_extension} ${EXECUTABLE_OUTPUT_PATH}/${name_without_extension}")
  endif()

endforeach()


#compile ext-test ones
file(GLOB_RECURSE TEST_DEPENDENCIES ${PROJECT_SOURCE_DIR}/tests/ext-tests/*.c)
foreach(file ${TEST_DEPENDENCIES})
	message ("\t${file} detected as necessary compile target for tests")
	get_filename_component (name_without_extension ${file} NAME_WE)
  	add_executable(${name_without_extension} ${file})
endforeach()

#listing dependencies of test (we should have done it automatically in the name)
add_dependencies(executor child-buf-controle)

set(list_lazy_tests ${list_lazy_tests} PARENT_SCOPE)
set(list_mandatory_tests ${list_mandatory_tests} PARENT_SCOPE)

#managing special dependencies
add_dependencies (integration authbreak)#integration test must provoke recompiling the soft
add_dependencies (integration basic_auth)#integration test must provoke recompiling the integration soft victim
add_dependencies (executor child-buf-controle)# child_buf is used by executor

add_dependencies (timer_test timer_precision)# timer call timer prcision
