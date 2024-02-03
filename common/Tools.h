///////////////////////////////////////////////////////////////////////////////
/// \file Tools.h
///////////////////////////////////////////////////////////////////////////////

/*
This file is part of the Robotics Toolbox.

Copyright (C) 2023

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

#ifndef TOOLS_H
#define TOOLS_H

#include <GlobalTypesDerived.h>

///////////////////////////////////////////////////////////////////////////////
/// \class Tools
///
/// \brief Class providing general helper functions.
///////////////////////////////////////////////////////////////////////////////
class Tools
{
public:
    ///////////////////////////////////////////////////////////////////////////////
    /// \brief     Check whether a value is already a member of a list or not.
    ///
    /// \param[in] ValueList    List containing all values.
    /// \param[in] ValueToCheck Value which shall be checked.
    ///
    /// \return    Flag whether the value is already a member of the list or not.
    ///////////////////////////////////////////////////////////////////////////////
    static boolean IsMember(const ListUInt64& ValueList,
                            const uint64      ValueToCheck);
};

#endif // TOOLS_H
