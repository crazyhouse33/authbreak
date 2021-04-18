set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} eprof)
target_link_libraries(${CMAKE_PROJECT_NAME} m) #linking with math

INSTALL(TARGETS authbreak
	RUNTIME DESTINATION authbreak
)



