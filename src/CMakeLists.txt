target_sources(portability
	PUBLIC
		FILE_SET CXX_MODULES
		FILES
			library.ixx
)

add_subdirectory(
	backend
)