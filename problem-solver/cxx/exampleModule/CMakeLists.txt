set(SC_EXAMPLE_MODULE_SRC "${PROBLEM_SOLVER_ROOT}/exampleModule")

set(SOURCES
		"exampleModule.cpp"
		"keynodes/keynodes.cpp"
		"agents/FindingOfLakesWithBiggerAreaAgent.cpp"
		)

set(HEADERS
		"exampleModule.hpp"
		"keynodes/keynodes.hpp"
		"agents/FindingOfLakesWithBiggerAreaAgent.hpp"
		)

include_directories(${SC_EXAMPLE_MODULE_SRC} ${SC_MEMORY_SRC} ${GLIB2_INCLUDE_DIRS})

add_library(exampleModule SHARED ${SOURCES} ${HEADERS})
add_dependencies(exampleModule sc-memory-cpp sc-kpm-common sc-agents-common)
target_link_libraries(exampleModule sc-memory-cpp sc-kpm-common sc-agents-common)

sc_codegen(exampleModule ${SC_EXAMPLE_MODULE_SRC})
SET(CMAKE_BUILD_TYPE Debug)
