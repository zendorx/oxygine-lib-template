cmake_minimum_required (VERSION 2.6)
project (OXYGINE_{{PROJECT}})

set(OXYGINE_{{PROJECT}}_INCLUDE_DIRS 
	${CMAKE_CURRENT_SOURCE_DIR}/src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${OXYGINE_{{PROJECT}}_INCLUDE_DIRS})
add_library(oxygine-{{project}} STATIC 
	src/{{project}}.cpp 
	src/{{project}}.h
	src/sim/{{Project}}Simulator.cpp 
	src/sim/{{Project}}Simulator.h
)

#target_link_libraries(oxyginemagicparticles)

set(OXYGINE_{{PROJECT}}_INCLUDE_DIRS ${OXYGINE_{{PROJECT}}_INCLUDE_DIRS} PARENT_SCOPE)
set(OXYGINE_{{PROJECT}}_LIBS ${OXYGINE_{{PROJECT}}_LIBS} PARENT_SCOPE)