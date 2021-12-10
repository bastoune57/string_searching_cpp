# find the sources
file(GLOB_RECURSE sources src/*.cpp)

# set up executable
add_executable(interview ${sources})
target_link_libraries(interview
	)
target_include_directories(interview PUBLIC
	)
target_compile_options(interview PUBLIC
	)
