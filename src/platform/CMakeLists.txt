# Platform module - CMake selects ONE source file based on target platform
# All files export the same module: synodic.portability.platform

if(WIN32)
	set(PLATFORM_MODULE windows.ixx)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	set(PLATFORM_MODULE linux.ixx)
elseif(APPLE)
	set(PLATFORM_MODULE macos.ixx)
else()
	set(PLATFORM_MODULE unknown.ixx)
endif()

# Allow user override for licensed/custom platforms
if(DEFINED PORTABILITY_PLATFORM_MODULE)
	set(PLATFORM_MODULE ${PORTABILITY_PLATFORM_MODULE})
endif()

target_sources(portability
	PUBLIC
	FILE_SET CXX_MODULES
	FILES
	${PLATFORM_MODULE}
)
