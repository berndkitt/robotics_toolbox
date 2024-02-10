///////////////////////////////////////////////////////////////////////////////
/// \file  Test_LIB$LIB_ABBREVIATION_UPPERCASE$Version.cpp
///
/// \brief Source file containing the unit tests for LIB$LIB_ABBREVIATION_UPPERCASE$Version.
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

#include "../../../source_code/include/LIB$LIB_ABBREVIATION_UPPERCASE$Version.h"
#include "../../../versioning/lib$LIB_ABBREVIATION$_Version.h"

// definition of macros for the unit tests
#define TEST_BUILDTIME_ISMATCHING           TEST ///< Define to get a unique test name.
#define TEST_BUILDUSER_ISMATCHING           TEST ///< Define to get a unique test name.
#define TEST_COMPILERINFORMATION_ISMATCHING TEST ///< Define to get a unique test name.
#define TEST_GITCOMMITHASH_ISMATCHING       TEST ///< Define to get a unique test name.
#define TEST_VERSIONSTRING_ISMATCHING       TEST ///< Define to get a unique test name.

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the build time.
///
/// Tests whether the provided build time does match the expected build time or
/// not.
///////////////////////////////////////////////////////////////////////////////
TEST_BUILDTIME_ISMATCHING(LIB$LIB_ABBREVIATION_UPPERCASE$Version, Test_BuildTime_IsMatching)
{
    ASSERT_EQ(LIB$LIB_ABBREVIATION_UPPERCASE$Version::GetBuildTime(), BuildTime);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the build user.
///
/// Tests whether the provided build user does match the expected build user or
/// not.
///////////////////////////////////////////////////////////////////////////////
TEST_BUILDUSER_ISMATCHING(LIB$LIB_ABBREVIATION_UPPERCASE$Version, Test_BuildUser_IsMatching)
{
    ASSERT_EQ(LIB$LIB_ABBREVIATION_UPPERCASE$Version::GetBuildUser(), BuildUser);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the compiler information.
///
/// Tests whether the provided compiler information does match the expected
/// compiler information or not.
///////////////////////////////////////////////////////////////////////////////
TEST_COMPILERINFORMATION_ISMATCHING(LIB$LIB_ABBREVIATION_UPPERCASE$Version, Test_CompilerInformation_IsMatching)
{
    std::string CompilerInformationExpected{CompilerIdentifier + " " + CompilerVersion};

    ASSERT_EQ(LIB$LIB_ABBREVIATION_UPPERCASE$Version::GetCompilerInformation(), CompilerInformationExpected);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the Git commit hash.
///
/// Tests whether the provided Git commit hash does match the expected Git
/// commit hash or not.
///////////////////////////////////////////////////////////////////////////////
TEST_GITCOMMITHASH_ISMATCHING(LIB$LIB_ABBREVIATION_UPPERCASE$Version, Test_GitCommitHash_IsMatching)
{
    ASSERT_EQ(LIB$LIB_ABBREVIATION_UPPERCASE$Version::GetGitCommitHash(), GitCommitHash);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the version string.
///
/// Tests whether the provided version string does match the expected version
/// string or not.
///////////////////////////////////////////////////////////////////////////////
TEST_VERSIONSTRING_ISMATCHING(LIB$LIB_ABBREVIATION_UPPERCASE$Version, Test_VersionString_IsMatching)
{
    std::string VersionStringExpected{"lib$LIB_ABBREVIATION$ v" + std::to_string(VersionMajor) + "." + std::to_string(VersionMinor) + "." + std::to_string(VersionPatch)};

    ASSERT_EQ(LIB$LIB_ABBREVIATION_UPPERCASE$Version::GetVersionString(), VersionStringExpected);
}
