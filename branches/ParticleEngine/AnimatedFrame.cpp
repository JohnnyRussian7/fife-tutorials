/**********************************************************************
*	Filename: AnimatedFrame.cpp
*	
*	Copyright (C) 2010, FIFE team
*	http://www.fifengine.net
*
*	This file is part of FIFE.
*
*	FIFE is free software: you can redistribute it and/or modify it
*	under the terms of the GNU Lesser General Public License as
*	published by the Free Software Foundation, either version 3 of
*	the License, or any later version.
*
*	FIFE is distributed in the hope that it will be useful,
*	but WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* 	GNU Lesser General Public License for more details.
*
*	You should have received a copy of the GNU Lesser General Public
*	License along with FIFE. If not, see http://www.gnu.org/licenses/.
***********************************************************************/

#include <sstream>

#include "AnimatedFrame.h"
#include "IAnimatedEntity.h"

namespace
{
    std::string CreateUniqueFrameName()
    {
        // automated counting for name generation, in case the user doesn't provide a name
        static uint32_t uniqueNumber = 0;
        static std::string baseName = "Frame";

        std::ostringstream oss;
        oss << baseName << "_" << uniqueNumber;

        const std::string name = oss.str();
        ++uniqueNumber;

        return name;
    }
}

AnimatedFrame::AnimatedFrame(IAnimatedEntity* owner, uint32_t frameNumber, const char* name) : m_owner(owner), m_frameNumber(frameNumber)
{
    if (!name)
    {
        m_name = CreateUniqueFrameName();
    }
    else
    {
        m_name = name;
    }
}

const char* AnimatedFrame::GetName() const
{
    return m_name.c_str();
}

uint32_t AnimatedFrame::GetFrameNumber() const
{
    return m_frameNumber;
}