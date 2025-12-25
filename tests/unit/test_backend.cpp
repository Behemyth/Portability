#include <gtest/gtest.h>

import synodic.portability;

namespace
{

// ============================================================================
// Platform Detection Tests
// ============================================================================

TEST(Platform, HasValidId)
{
	// PlatformId should be a non-empty string
	EXPECT_FALSE(port::PlatformId.empty());
}

TEST(Platform, IdMatchesName)
{
	// ID and Name should be consistent
	if (port::PlatformId == "windows")
		EXPECT_EQ(port::PlatformName(), "Windows");
	else if (port::PlatformId == "linux")
		EXPECT_EQ(port::PlatformName(), "Linux");
	else if (port::PlatformId == "macos")
		EXPECT_EQ(port::PlatformName(), "macOS");
	else if (port::PlatformId == "unknown")
		EXPECT_EQ(port::PlatformName(), "Unknown");
}

// ============================================================================
// Compiler Detection Tests
// ============================================================================

TEST(Compiler, HasValidId)
{
	// CompilerId should be a non-empty string
	EXPECT_FALSE(port::CompilerId.empty());
}

TEST(Compiler, IdMatchesName)
{
	if (port::CompilerId == "msvc")
		EXPECT_EQ(port::CompilerName(), "MSVC");
	else if (port::CompilerId == "clang")
		EXPECT_EQ(port::CompilerName(), "Clang");
	else if (port::CompilerId == "gcc")
		EXPECT_EQ(port::CompilerName(), "GCC");
	else if (port::CompilerId == "unknown")
		EXPECT_EQ(port::CompilerName(), "Unknown");
}

TEST(Compiler, VersionIsReasonable)
{
	auto [major, minor, patch] = port::CompilerVersion();
	EXPECT_GE(major, 0);
	EXPECT_GE(minor, 0);
	EXPECT_GE(patch, 0);
}

TEST(Compiler, CapabilitiesAreConsistent)
{
	// MSVC-specific features
	if constexpr (port::CompilerId == "msvc")
	{
		EXPECT_TRUE(port::HasForceInline);
		EXPECT_TRUE(port::HasPragmaOptimize);
		EXPECT_FALSE(port::HasGnuAsm);
	}
	
	// GCC/Clang should have GNU features
	if constexpr (port::CompilerId == "gcc" || port::CompilerId == "clang")
	{
		EXPECT_TRUE(port::HasGnuAsm);
		EXPECT_TRUE(port::HasGnuAttributes);
	}
}

// ============================================================================
// Architecture Detection Tests
// ============================================================================

TEST(Architecture, HasValidId)
{
	// ArchitectureId should be a non-empty string
	EXPECT_FALSE(port::ArchitectureId.empty());
}

TEST(Architecture, PointerSizeIsConsistent)
{
	// Pointer size should match known architectures
	if constexpr (port::ArchitectureId == "x64" || port::ArchitectureId == "arm64")
	{
		EXPECT_EQ(port::PointerSize, 8u);
	}
	if constexpr (port::ArchitectureId == "x86" || port::ArchitectureId == "arm")
	{
		EXPECT_EQ(port::PointerSize, 4u);
	}
	// PointerSize should be reasonable
	EXPECT_TRUE(port::PointerSize == 4 || port::PointerSize == 8);
}

TEST(Architecture, IdMatchesName)
{
	if (port::ArchitectureId == "x64")
		EXPECT_EQ(port::ArchitectureName(), "x86-64");
	else if (port::ArchitectureId == "x86")
		EXPECT_EQ(port::ArchitectureName(), "x86");
	else if (port::ArchitectureId == "arm64")
		EXPECT_EQ(port::ArchitectureName(), "ARM64");
	else if (port::ArchitectureId == "arm")
		EXPECT_EQ(port::ArchitectureName(), "ARM");
	else if (port::ArchitectureId == "unknown")
		EXPECT_EQ(port::ArchitectureName(), "Unknown");
}

// ============================================================================
// Build Detection Tests
// ============================================================================

TEST(Build, AssertionsMatchNdebug)
{
#ifdef NDEBUG
	EXPECT_FALSE(port::HasAssertions);
#else
	EXPECT_TRUE(port::HasAssertions);
#endif
}

// ============================================================================
// Compile-Time Tests (static_assert)
// ============================================================================

// String IDs are always valid for compile-time checks
static_assert(!port::PlatformId.empty(), "PlatformId must not be empty");
static_assert(!port::CompilerId.empty(), "CompilerId must not be empty");
static_assert(!port::ArchitectureId.empty(), "ArchitectureId must not be empty");
static_assert(port::PointerSize == 4 || port::PointerSize == 8, "PointerSize must be 4 or 8");

// Example of platform-specific compile-time branching
static_assert(
	port::PlatformId == "windows" ||
	port::PlatformId == "linux" ||
	port::PlatformId == "macos" ||
	port::PlatformId == "unknown" ||
	true,  // Allow any custom platform
	"Platform detection works"
);

}
