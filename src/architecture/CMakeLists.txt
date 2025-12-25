# Architecture module - CMake selects ONE source file based on target architecture
# All files export the same module: synodic.portability.architecture

# Determine architecture from CMake
if(CMAKE_SYSTEM_PROCESSOR MATCHES "AMD64|x86_64|x64")
	set(ARCH_MODULE x64.ixx)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "i[3-6]86|x86")
	set(ARCH_MODULE x86.ixx)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|ARM64")
	set(ARCH_MODULE arm64.ixx)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
	set(ARCH_MODULE arm.ixx)
else()
	set(ARCH_MODULE unknown.ixx)
endif()

# Allow user override
if(DEFINED PORTABILITY_ARCHITECTURE_MODULE)
	set(ARCH_MODULE ${PORTABILITY_ARCHITECTURE_MODULE})
endif()

target_sources(portability
	PUBLIC
	FILE_SET CXX_MODULES
	FILES
	${ARCH_MODULE}
)
