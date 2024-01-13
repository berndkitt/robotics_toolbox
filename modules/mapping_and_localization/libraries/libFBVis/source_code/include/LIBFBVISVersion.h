///////////////////////////////////////////////////////////////////////////////
/// \file  LIBFBVISVersion.h
///
/// \brief Header file containing the LIBFBVISVersion class.
///////////////////////////////////////////////////////////////////////////////

/*
This file is part of the Robotics Toolbox.

Copyright (C) 2021

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

#ifndef LIBFBVISVERSION_H
#define LIBFBVISVERSION_H

#include <string>

#include <GlobalTypesBase.h>

///////////////////////////////////////////////////////////////////////////////
/// \class LIBFBVISVersion
///
/// \brief Class containing the version information of libFBVis.
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
class LIBFBVISVersion
{
public: // public methods
    ///////////////////////////////////////////////////////////////////////////////
    /// \brief  Getter for the time when the library was built.
    ///
    /// \return Time when the library was built.
    ///////////////////////////////////////////////////////////////////////////////
    static std::string GetBuildTime();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief  Getter for the user who built the library.
    ///
    /// \return User who built the library.
    ///////////////////////////////////////////////////////////////////////////////
    static std::string GetBuildUser();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief  Getter for the compiler identifier.
    ///
    /// \return Compiler identifier.
    ///////////////////////////////////////////////////////////////////////////////
    static std::string GetCompilerIdentifier();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief  Getter for the compiler version.
    ///
    /// \return Compiler version.
    ///////////////////////////////////////////////////////////////////////////////
    static std::string GetCompilerVersion();
    
    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Getter for the Git commit hash.
    ///
    /// \return Git commit hash.
    ///////////////////////////////////////////////////////////////////////////////
    static std::string GetGitCommitHash();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief  Getter for the major version number of the library.
    ///
    /// \return Major version number of the library.
    ///////////////////////////////////////////////////////////////////////////////
    static uint64 GetVersionMajor();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief  Getter for the minor version number of the library.
    ///
    /// \return Minor version number of the library.
    ///////////////////////////////////////////////////////////////////////////////
    static uint64 GetVersionMinor();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief  Getter for the patch version number of the library.
    ///
    /// \return Patch version number of the library.
    ///////////////////////////////////////////////////////////////////////////////
    static uint64 GetVersionPatch();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief     Getter for the library version as string.
    ///
    /// Returns the complete version number of the library as string. The
    /// additional parameter can be used to add the name of the library in front of
    /// the version number.
    ///
    /// \param[in] AddLibraryName Add the name of the library in front of the version.
    ///
    /// \return    Library version as string.
    ///////////////////////////////////////////////////////////////////////////////
    static std::string GetVersionString(const boolean AddLibraryName = true);
};

#endif // LIBFBVISVERSION_H
