///////////////////////////////////////////////////////////////////////////////
/// \file  LIBWPGVersion.cpp
///
/// \brief Source file containing the LIBWPGVersion class.
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

#include "../include/LIBWPGVersion.h"
#include "../../versioning/libWPG_Version.h"

std::string LIBWPGVersion::GetBuildTime()
{
    return BuildTime;
}

std::string LIBWPGVersion::GetBuildUser()
{
    return BuildUser;
}

std::string LIBWPGVersion::GetGitCommitHash()
{
    return GitCommitHash;
}

uint64 LIBWPGVersion::GetVersionMajor()
{
    return VersionMajor;
}

uint64 LIBWPGVersion::GetVersionMinor()
{
    return VersionMinor;
}

uint64 LIBWPGVersion::GetVersionPatch()
{
    return VersionPatch;
}

std::string LIBWPGVersion::GetVersionString(const boolean AddLibraryName)
{
    std::string VersionString {"v" + std::to_string(VersionMajor) + "." + std::to_string(VersionMinor) + "." + std::to_string(VersionPatch)};

    if(AddLibraryName)
    {
        VersionString = "libWPG " + VersionString;
    }

    return VersionString;
}
