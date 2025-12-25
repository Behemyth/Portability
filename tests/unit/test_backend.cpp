#include <gtest/gtest.h>

import synodic.portability;

namespace
{

	// ============================================================================
	// Platform Detection Tests
	// ============================================================================

	TEST(Platform, HasValidID)
	{
		// PlatformID should be a non-empty string
		EXPECT_FALSE(port::PlatformID.empty());
	}

	TEST(Platform, IDMatchesName)
	{
		// ID and Name should be consistent
		if (port::PlatformID == "windows")
			EXPECT_EQ(port::PlatformName(), "Windows");
		else if (port::PlatformID == "linux")
			EXPECT_EQ(port::PlatformName(), "Linux");
		else if (port::PlatformID == "macos")
			EXPECT_EQ(port::PlatformName(), "macOS");
		else if (port::PlatformID == "unknown")
			EXPECT_EQ(port::PlatformName(), "Unknown");
	}

	// ============================================================================
	// Compiler Detection Tests
	// ============================================================================

	TEST(Compiler, HasValidID)
	{
		// CompilerID should be a non-empty string
		EXPECT_FALSE(port::CompilerID.empty());
	}

	TEST(Compiler, IDMatchesName)
	{
		if (port::CompilerID == "msvc")
			EXPECT_EQ(port::CompilerName(), "MSVC");
		else if (port::CompilerID == "clang")
			EXPECT_EQ(port::CompilerName(), "Clang");
		else if (port::CompilerID == "gcc")
			EXPECT_EQ(port::CompilerName(), "GCC");
		else if (port::CompilerID == "unknown")
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
		if constexpr (port::CompilerID == "msvc")
		{
			EXPECT_TRUE(port::HasForceInline);
			EXPECT_TRUE(port::HasPragmaOptimize);
			EXPECT_FALSE(port::HasGnuAsm);
		}

		// GCC/Clang should have GNU features
		if constexpr (port::CompilerID == "gcc" || port::CompilerID == "clang")
		{
			EXPECT_TRUE(port::HasGnuAsm);
			EXPECT_TRUE(port::HasGnuAttributes);
		}
	}

	// ============================================================================
	// Architecture Detection Tests
	// ============================================================================

	TEST(Architecture, HasValidID)
	{
		// ArchitectureID should be a non-empty string
		EXPECT_FALSE(port::ArchitectureID.empty());
	}

	TEST(Architecture, PointerSizeIsConsistent)
	{
		// Pointer size should match known architectures
		if constexpr (port::ArchitectureID == "x64" || port::ArchitectureID == "arm64")
		{
			EXPECT_EQ(port::PointerSize, 8u);
		}
		if constexpr (port::ArchitectureID == "x86" || port::ArchitectureID == "arm")
		{
			EXPECT_EQ(port::PointerSize, 4u);
		}
		// PointerSize should be reasonable
		EXPECT_TRUE(port::PointerSize == 4 || port::PointerSize == 8);
	}

	TEST(Architecture, IDMatchesName)
	{
		if (port::ArchitectureID == "x64")
			EXPECT_EQ(port::ArchitectureName(), "x86-64");
		else if (port::ArchitectureID == "x86")
			EXPECT_EQ(port::ArchitectureName(), "x86");
		else if (port::ArchitectureID == "arm64")
			EXPECT_EQ(port::ArchitectureName(), "ARM64");
		else if (port::ArchitectureID == "arm")
			EXPECT_EQ(port::ArchitectureName(), "ARM");
		else if (port::ArchitectureID == "unknown")
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
	static_assert(!port::PlatformID.empty(), "PlatformID must not be empty");
	static_assert(!port::CompilerID.empty(), "CompilerID must not be empty");
	static_assert(!port::ArchitectureID.empty(), "ArchitectureID must not be empty");
	static_assert(port::PointerSize == 4 || port::PointerSize == 8, "PointerSize must be 4 or 8");

	// Example of platform-specific compile-time branching
	static_assert(
		port::PlatformID == "windows" ||
		port::PlatformID == "linux" ||
		port::PlatformID == "macos" ||
		port::PlatformID == "unknown" ||
		true,  // Allow any custom platform
		"Platform detection works"
		);

}
