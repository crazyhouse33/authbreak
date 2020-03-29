message(tamere)
set (testbin ${CMAKE_PROJECT_NAME}_test_all)

#file(GLOB_RECURSE TEST_SOURCES *.h *.c)
#add_executable(${CMAKE_PROJECT_NAME}_test_all ${TEST_SOURCES})

add_executable(testcli atnjdgk.c)

add_test( all COMMAND testcli)

