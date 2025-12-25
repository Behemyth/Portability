target_sources(portability
	PUBLIC
	FILE_SET CXX_MODULES
	FILES
	msvc.ixx
	clang.ixx
	gcc.ixx
)
