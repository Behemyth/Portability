# Compiler module - CMake selects ONE source file based on compiler
# All files export the same module: synodic.portability.compiler

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
	set(COMPILER_MODULE clang.ixx)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set(COMPILER_MODULE gcc.ixx)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	set(COMPILER_MODULE msvc.ixx)
else()
	set(COMPILER_MODULE unknown.ixx)
endif()

# Allow user override for custom compilers
if(DEFINED PORTABILITY_COMPILER_MODULE)
	set(COMPILER_MODULE ${PORTABILITY_COMPILER_MODULE})
endif()

target_sources(portability
	PUBLIC
	FILE_SET CXX_MODULES
	FILES
	${COMPILER_MODULE}
)
