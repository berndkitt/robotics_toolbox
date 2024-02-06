///////////////////////////////////////////////////////////////////////////////
/// \file  LIB${LIB_ABBREVIATION}Version.cpp
///
/// \brief Source file containing the LIB${LIB_ABBREVIATION}Version class.
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

#include "../include/LIB${LIB_ABBREVIATION}Version.h"
#include "../../versioning/lib${LIB_ABBREVIATION}_Version.h"

std::string LIB${LIB_ABBREVIATION}Version::GetBuildTime()
{
    return BuildTime;
}

std::string LIB${LIB_ABBREVIATION}Version::GetBuildUser()
{
    return BuildUser;
}

std::string LIB${LIB_ABBREVIATION}Version::GetCompilerIdentifier()
{
    return CompilerIdentifier;
}

std::string LIB${LIB_ABBREVIATION}Version::GetCompilerVersion()
{
    return CompilerVersion;
}

std::string LIB${LIB_ABBREVIATION}Version::GetGitCommitHash()
{
    return GitCommitHash;
}

uint64 LIB${LIB_ABBREVIATION}Version::GetVersionMajor()
{
    return VersionMajor;
}

uint64 LIB${LIB_ABBREVIATION}Version::GetVersionMinor()
{
    return VersionMinor;
}

uint64 LIB${LIB_ABBREVIATION}Version::GetVersionPatch()
{
    return VersionPatch;
}

std::string LIB${LIB_ABBREVIATION}Version::GetVersionString(const boolean AddLibraryName)
{
    std::string VersionString{"v" + std::to_string(VersionMajor) + "." + std::to_string(VersionMinor) + "." + std::to_string(VersionPatch)};

    if(AddLibraryName)
    {
        VersionString = "lib${LIB_ABBREVIATION} " + VersionString;
    }

    return VersionString;
}
