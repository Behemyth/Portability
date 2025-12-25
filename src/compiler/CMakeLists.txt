target_sources(portability
	PUBLIC
	FILE_SET CXX_MODULES
	FILES
	compiler.ixx
)

add_subdirectory(backend)
