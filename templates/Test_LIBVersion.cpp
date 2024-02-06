///////////////////////////////////////////////////////////////////////////////
/// \file  Test_LIB${LIB_ABBREVIATION_UPPERCASE}$Version.cpp
///
/// \brief Source file containing the unit tests for LIB${LIB_ABBREVIATION_UPPERCASE}$Version.
///////////////////////////////////////////////////////////////////////////////

/*
This file is part of the Robotics Toolbox.

Copyright (C) 2024

Authors: Bernd Kitt (b.kitt@berndkitt.de)

The Robotics Toolbox is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 3 of the License,
or any later version.

The Robotics Toolbox is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
Public License for more details.

You should have received a copy of the GNU General Public License along with
the Robotics Toolbox. If not, see https://www.gnu.org/licenses/.
*/

#include <gtest/gtest.h>

#include "../../../source_code/include/LIB${LIB_ABBREVIATION_UPPERCASE}$Version.h"
#include "../../../versioning/lib${LIB_ABBREVIATION}$_Version.h"

// definition of macros for the unit tests
#define TEST_BUILDTIME_ISMATCHING                                    TEST ///< Define to get a unique test name.
#define TEST_BUILDUSER_ISMATCHING                                    TEST ///< Define to get a unique test name.
#define TEST_COMPILERIDENTIFER_ISMATCHING                            TEST ///< Define to get a unique test name.
#define TEST_COMPILERVERSION_ISMATCHING                              TEST ///< Define to get a unique test name.
#define TEST_GITCOMMITHASH_ISMATCHING                                TEST ///< Define to get a unique test name.
#define TEST_VERSIONMAJOR_ISMATCHING                                 TEST ///< Define to get a unique test name.
#define TEST_VERSIONMINOR_ISMATCHING                                 TEST ///< Define to get a unique test name.
#define TEST_VERSIONPATCH_ISMATCHING                                 TEST ///< Define to get a unique test name.
#define TEST_VERSIONSTRINGWITHLIBRARYNAME_DEFAULTARGUMENT_ISMATCHING TEST ///< Define to get a unique test name.
#define TEST_VERSIONSTRINGWITHLIBRARYNAME_ISMATCHING                 TEST ///< Define to get a unique test name.
#define TEST_VERSIONSTRINGWITHOUTLIBRARYNAME_ISMATCHING              TEST ///< Define to get a unique test name.

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the build time.
///
/// Tests whether the provided build time does match the expected build time or
/// not.
///////////////////////////////////////////////////////////////////////////////
TEST_BUILDTIME_ISMATCHING(LIB${LIB_ABBREVIATION_UPPERCASE}$Version, Test_BuildTime_IsMatching)
{
    ASSERT_EQ(LIB${LIB_ABBREVIATION_UPPERCASE}$Version::GetBuildTime(), BuildTime);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the build user.
///
/// Tests whether the provided build user does match the expected build user or
/// not.
///////////////////////////////////////////////////////////////////////////////
TEST_BUILDUSER_ISMATCHING(LIB${LIB_ABBREVIATION_UPPERCASE}$Version, Test_BuildUser_IsMatching)
{
    ASSERT_EQ(LIB${LIB_ABBREVIATION_UPPERCASE}$Version::GetBuildUser(), BuildUser);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the compiler identifier.
///
/// Tests whether the provided compiler identifier does match the expected
/// compiler identifier or not.
///////////////////////////////////////////////////////////////////////////////
TEST_COMPILERIDENTIFER_ISMATCHING(LIB${LIB_ABBREVIATION_UPPERCASE}$Version, Test_CompilerIdentifier_IsMatching)
{
    ASSERT_EQ(LIB${LIB_ABBREVIATION_UPPERCASE}$Version::GetCompilerIdentifier(), CompilerIdentifier);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the compiler version.
///
/// Tests whether the provided compiler version does match the expected
/// compiler version or not.
///////////////////////////////////////////////////////////////////////////////
TEST_COMPILERVERSION_ISMATCHING(LIB${LIB_ABBREVIATION_UPPERCASE}$Version, Test_CompilerVersion_IsMatching)
{
    ASSERT_EQ(LIB${LIB_ABBREVIATION_UPPERCASE}$Version::GetCompilerVersion(), CompilerVersion);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the Git commit hash.
///
/// Tests whether the provided Git commit hash does match the expected Git
/// commit hash or not.
///////////////////////////////////////////////////////////////////////////////
TEST_GITCOMMITHASH_ISMATCHING(LIB${LIB_ABBREVIATION_UPPERCASE}$Version, Test_GitCommitHash_IsMatching)
{
    ASSERT_EQ(LIB${LIB_ABBREVIATION_UPPERCASE}$Version::GetGitCommitHash(), GitCommitHash);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the major version number.
///
/// Tests whether the provided major version number does match the expected
/// major version number or not.
///////////////////////////////////////////////////////////////////////////////
TEST_VERSIONMAJOR_ISMATCHING(LIB${LIB_ABBREVIATION_UPPERCASE}$Version, Test_VersionMajor_IsMatching)
{
    ASSERT_EQ(LIB${LIB_ABBREVIATION_UPPERCASE}$Version::GetVersionMajor(), VersionMajor);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the minor version number.
///
/// Tests whether the provided minor version number does match the expected
/// minor version number or not.
///////////////////////////////////////////////////////////////////////////////
TEST_VERSIONMINOR_ISMATCHING(LIB${LIB_ABBREVIATION_UPPERCASE}$Version, Test_VersionMinor_IsMatching)
{
    ASSERT_EQ(LIB${LIB_ABBREVIATION_UPPERCASE}$Version::GetVersionMinor(), VersionMinor);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the patch version number.
///
/// Tests whether the provided patch version number does match the expected
/// patch version number or not.
///////////////////////////////////////////////////////////////////////////////
TEST_VERSIONPATCH_ISMATCHING(LIB${LIB_ABBREVIATION_UPPERCASE}$Version, Test_VersionPatch_IsMatching)
{
    ASSERT_EQ(LIB${LIB_ABBREVIATION_UPPERCASE}$Version::GetVersionPatch(), VersionPatch);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the version number.
///
/// Tests whether the provided version number does match the expected version
/// number or not. The default argument is used. Hence, the name of the library
/// is expected to be in front of the version number.
///////////////////////////////////////////////////////////////////////////////
TEST_VERSIONSTRINGWITHLIBRARYNAME_DEFAULTARGUMENT_ISMATCHING(LIB${LIB_ABBREVIATION_UPPERCASE}$Version, Test_VersionStringWithLibraryName_DefaultArgument_IsMatching)
{
    std::string VersionStringExpected{"lib${LIB_ABBREVIATION}$ v" + std::to_string(VersionMajor) + "." + std::to_string(VersionMinor) + "." + std::to_string(VersionPatch)};

    ASSERT_EQ(LIB${LIB_ABBREVIATION_UPPERCASE}$Version::GetVersionString(), VersionStringExpected);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the version number.
///
/// Tests whether the provided version number does match the expected version
/// number or not. The argument is set to "true". Hence, the name of the
/// library is expected to be in front of the version number.
///////////////////////////////////////////////////////////////////////////////
TEST_VERSIONSTRINGWITHLIBRARYNAME_ISMATCHING(LIB${LIB_ABBREVIATION_UPPERCASE}$Version, Test_VersionStringWithLibraryName_IsMatching)
{
    std::string VersionStringExpected{"lib${LIB_ABBREVIATION}$ v" + std::to_string(VersionMajor) + "." + std::to_string(VersionMinor) + "." + std::to_string(VersionPatch)};

    ASSERT_EQ(LIB${LIB_ABBREVIATION_UPPERCASE}$Version::GetVersionString(true), VersionStringExpected);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the version number.
///
/// Tests whether the provided version number does match the expected version
/// number or not. The argument is set to "false". Hence, the name of the
/// library is not expected to be in front of the version number.
///////////////////////////////////////////////////////////////////////////////
TEST_VERSIONSTRINGWITHOUTLIBRARYNAME_ISMATCHING(LIB${LIB_ABBREVIATION_UPPERCASE}$Version, Test_VersionStringWithoutLibraryName_IsMatching)
{
    std::string VersionStringExpected{"v" + std::to_string(VersionMajor) + "." + std::to_string(VersionMinor) + "." + std::to_string(VersionPatch)};

    ASSERT_EQ(LIB${LIB_ABBREVIATION_UPPERCASE}$Version::GetVersionString(false), VersionStringExpected);
}
