target_sources(portability
	PUBLIC
		FILE_SET CXX_MODULES
		FILES
			core.ixx
			portability.ixx
)

add_subdirectory(platform)
add_subdirectory(compiler)
add_subdirectory(architecture)
add_subdirectory(build)