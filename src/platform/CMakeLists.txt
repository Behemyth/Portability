target_sources(portability
	PUBLIC
	FILE_SET CXX_MODULES
	FILES
	platform.ixx
)

add_subdirectory(backend)
