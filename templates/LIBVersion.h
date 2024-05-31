///////////////////////////////////////////////////////////////////////////////
/// \file  LIB$LIB_ABBREVIATION_UPPERCASE$Version.h
///
/// \brief Header file containing the LIB$LIB_ABBREVIATION_UPPERCASE$Version class.
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

#ifndef LIB$LIB_ABBREVIATION_UPPERCASE$VERSION_H
#define LIB$LIB_ABBREVIATION_UPPERCASE$VERSION_H

#include <string>

#include <GlobalTypesBase.h>

///////////////////////////////////////////////////////////////////////////////
/// \class LIB$LIB_ABBREVIATION_UPPERCASE$Version
///
/// \brief Class containing the version information of lib$LIB_ABBREVIATION$.
///
/// The release numbers of the library follow the Semantic Versioning scheme.
/// Hence, a version number has the following format: MAJOR.MINOR.PATCH
///
/// Besides the actual version number, the class also contains the build
/// information of the library.
/// - Time when the library was built.
/// - Git commit hash.
/// - User who built the library.
///////////////////////////////////////////////////////////////////////////////
class LIB$LIB_ABBREVIATION_UPPERCASE$Version
{
public:
    ///////////////////////////////////////////////////////////////////////////////
    /// \brief  Getter for the time when the library was built.
    ///
    /// \return Time when the library was built.
    ///////////////////////////////////////////////////////////////////////////////
    static std::string GetBuildTime();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief  Getter for the build type.
    ///
    /// \return Build type.
    ///////////////////////////////////////////////////////////////////////////////
    static std::string GetBuildType();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief  Getter for the user who built the library.
    ///
    /// \return User who built the library.
    ///////////////////////////////////////////////////////////////////////////////
    static std::string GetBuildUser();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief  Getter for the compiler information.
    ///
    /// \return Compiler information.
    ///////////////////////////////////////////////////////////////////////////////
    static std::string GetCompilerInformation();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief  Getter for the Git commit hash.
    ///
    /// \return Git commit hash.
    ///////////////////////////////////////////////////////////////////////////////
    static std::string GetGitCommitHash();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief  Getter for the library version as string.
    ///
    /// Returns the library version as string.
    ///
    /// \return Library version as string.
    ///////////////////////////////////////////////////////////////////////////////
    static std::string GetVersionString();
};

#endif // LIB$LIB_ABBREVIATION_UPPERCASE$VERSION_H
