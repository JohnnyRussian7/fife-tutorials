/**********************************************************************
*	Filename: PolygonWindingMode.h
*	
*	Copyright (C) 2011, FIFE team
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
#ifndef POLYGONWINDINGMODE_H_
#define POLYGONWINDINGMODE_H_

struct WindingType
{
    enum Enum
    {
        Clockwise = 0,
        CounterClockwise,
        
        Max,
        Invalid = -1
    };
    
    static bool IsValid(Enum type)
    {
        return (type > Invalid && type < Max);
    }
};

class PolygonWindingMode
{
public:
    //!***************************************************************
    //! @details:
    //! constructor
    //!
    //! @note: 
    //! default is to set to counter-clockwise
    //!***************************************************************
    PolygonWindingMode();

    //!***************************************************************
    //! @details:
    //! sets the winding type to use
    //!***************************************************************
    void SetWindingType(WindingType::Enum windingType);

    //!***************************************************************
    //! @details:
    //! accessor for the winding type
    //!***************************************************************
    WindingType::Enum GetWindingType() const;

private:
    WindingType::Enum m_windingType;
};

bool operator==(const PolygonWindingMode& lhs, const PolygonWindingMode& rhs);
bool operator!=(const PolygonWindingMode& lhs, const PolygonWindingMode& rhs);

#endif
