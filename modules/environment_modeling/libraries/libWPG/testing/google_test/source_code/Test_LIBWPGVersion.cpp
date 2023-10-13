///////////////////////////////////////////////////////////////////////////////
/// \file Test_LIBWPGVersion.cpp
///////////////////////////////////////////////////////////////////////////////

/*
This file is part of the Robotics Toolbox.

Copyright (C) 2022

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

#include "../../../source_code/include/LIBWPGVersion.h"
#include "../../../versioning/libWPG_Version.h"

// definition of macros for the unit tests
#define TEST_BUILD_TIME_IS_FITTING                                        TEST  ///< Define to get a unique test name.
#define TEST_BUILD_USER_IS_FITTING                                        TEST  ///< Define to get a unique test name.
#define TEST_GIT_COMMIT_HASH_IS_FITTING                                   TEST  ///< Define to get a unique test name.
#define TEST_VERSION_MAJOR_IS_FITTING                                     TEST  ///< Define to get a unique test name.
#define TEST_VERSION_MINOR_IS_FITTING                                     TEST  ///< Define to get a unique test name.
#define TEST_VERSION_PATCH_IS_FITTING                                     TEST  ///< Define to get a unique test name.
#define TEST_VERSION_STRING_WITH_LIBRARY_NAME_DEFAULT_ARGUMENT_IS_FITTING TEST  ///< Define to get a unique test name.
#define TEST_VERSION_STRING_WITH_LIBRARY_NAME_IS_FITTING                  TEST  ///< Define to get a unique test name.
#define TEST_VERSION_STRING_WITHOUT_LIBRARY_NAME_IS_FITTING               TEST  ///< Define to get a unique test name.

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the build time.
///
/// Tests whether the provided build time does match the expected build time or
/// not.
///////////////////////////////////////////////////////////////////////////////
TEST_BUILD_TIME_IS_FITTING(LIBWPGVersion, Test_Build_Time_Is_Fitting)
{
    ASSERT_EQ(LIBWPGVersion::GetBuildTime(), BuildTime);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the build user.
///
/// Tests whether the provided build user does match the expected build user or
/// not.
///////////////////////////////////////////////////////////////////////////////
TEST_BUILD_USER_IS_FITTING(LIBWPGVersion, Test_Build_User_Is_Fitting)
{
    ASSERT_EQ(LIBWPGVersion::GetBuildUser(), BuildUser);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the Git commit hash.
///
/// Tests whether the provided Git commit hash does match the expected Git
/// commit hash or not.
///////////////////////////////////////////////////////////////////////////////
TEST_GIT_COMMIT_HASH_IS_FITTING(LIBWPGVersion, Test_Git_Commit_Hash_Is_Fitting)
{
    ASSERT_EQ(LIBWPGVersion::GetGitCommitHash(), GitCommitHash);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the major version number.
///
/// Tests whether the provided major version number does match the expected
/// major version number or not.
///////////////////////////////////////////////////////////////////////////////
TEST_VERSION_MAJOR_IS_FITTING(LIBWPGVersion, Test_Version_Major_Is_Fitting)
{
    ASSERT_EQ(LIBWPGVersion::GetVersionMajor(), VersionMajor);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the minor version number.
///
/// Tests whether the provided minor version number does match the expected
/// minor version number or not.
///////////////////////////////////////////////////////////////////////////////
TEST_VERSION_MINOR_IS_FITTING(LIBWPGVersion, Test_Version_Minor_Is_Fitting)
{
    ASSERT_EQ(LIBWPGVersion::GetVersionMinor(), VersionMinor);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the patch version number.
///
/// Tests whether the provided patch version number does match the expected
/// patch version number or not.
///////////////////////////////////////////////////////////////////////////////
TEST_VERSION_PATCH_IS_FITTING(LIBWPGVersion, Test_Version_Patch_Is_Fitting)
{
    ASSERT_EQ(LIBWPGVersion::GetVersionPatch(), VersionPatch);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the version number.
///
/// Tests whether the provided version number does match the expected version
/// number or not. The default argument is used. Hence, the name of the library
/// is expected to be in front of the version number.
///////////////////////////////////////////////////////////////////////////////
TEST_VERSION_STRING_WITH_LIBRARY_NAME_DEFAULT_ARGUMENT_IS_FITTING(LIBWPGVersion, Test_Version_String_With_Library_Name_Default_Argument_Is_Fitting)
{
    std::string VersionStringExpected = "libWPG v" + std::to_string(VersionMajor) + "." + std::to_string(VersionMinor) + "." + std::to_string(VersionPatch);

    ASSERT_EQ(LIBWPGVersion::GetVersionString(), VersionStringExpected);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the version number.
///
/// Tests whether the provided version number does match the expected version
/// number or not. The argument is set to "true". Hence, the name of the
/// library is expected to be in front of the version number.
///////////////////////////////////////////////////////////////////////////////
TEST_VERSION_STRING_WITH_LIBRARY_NAME_IS_FITTING(LIBWPGVersion, Test_Version_String_With_Library_Name_Is_Fitting)
{
    std::string VersionStringExpected = "libWPG v" + std::to_string(VersionMajor) + "." + std::to_string(VersionMinor) + "." + std::to_string(VersionPatch);

    ASSERT_EQ(LIBWPGVersion::GetVersionString(true), VersionStringExpected);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the version number.
///
/// Tests whether the provided version number does match the expected version
/// number or not. The argument is set to "false". Hence, the name of the
/// library is not expected to be in front of the version number.
///////////////////////////////////////////////////////////////////////////////
TEST_VERSION_STRING_WITHOUT_LIBRARY_NAME_IS_FITTING(LIBWPGVersion, Test_Version_String_Without_Library_Name_Is_Fitting)
{
    std::string VersionStringExpected = "v" + std::to_string(VersionMajor) + "." + std::to_string(VersionMinor) + "." + std::to_string(VersionPatch);

    ASSERT_EQ(LIBWPGVersion::GetVersionString(false), VersionStringExpected);
}
