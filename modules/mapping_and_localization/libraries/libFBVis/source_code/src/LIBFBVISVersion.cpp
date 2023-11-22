///////////////////////////////////////////////////////////////////////////////
/// \file LIBFBVISVersion.cpp
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

#include "../include/LIBFBVISVersion.h"
#include "../../versioning/libFBVis_Version.h"

std::string LIBFBVISVersion::GetBuildTime()
{
    return BuildTime;
}

std::string LIBFBVISVersion::GetBuildUser()
{
    return BuildUser;
}

std::string LIBFBVISVersion::GetGitCommitHash()
{
    return GitCommitHash;
}

uint64 LIBFBVISVersion::GetVersionMajor()
{
    return VersionMajor;
}

uint64 LIBFBVISVersion::GetVersionMinor()
{
    return VersionMinor;
}

uint64 LIBFBVISVersion::GetVersionPatch()
{
    return VersionPatch;
}

std::string LIBFBVISVersion::GetVersionString(const boolean AddLibraryName)
{
    std::string VersionString {"v" + std::to_string(VersionMajor) + "." + std::to_string(VersionMinor) + "." + std::to_string(VersionPatch)};

    if(AddLibraryName)
    {
        VersionString = "libFBVis " + VersionString;
    }

    return VersionString;
}
