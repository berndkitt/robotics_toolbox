///////////////////////////////////////////////////////////////////////////////
/// \file Tools.cpp
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

#include <Tools.h>

boolean Tools::IsMember(const ListUInt64& ValueList,
                        const uint64      ValueToCheck)
{
    // create output variable
    boolean ValueIsMember{false};

    // get number of entries in the list
    const uint64 NumberOfEntries{ValueList.size()};

    // check whether the value is already a member of the list or not
    for(uint64 i_Value{0U}; i_Value < NumberOfEntries; i_Value++)
    {
        const uint64 CurrentValue{ValueList[i_Value]};

        if(CurrentValue == ValueToCheck)
        {
            ValueIsMember = true;

            break;
        }
    }

    return ValueIsMember;
}
