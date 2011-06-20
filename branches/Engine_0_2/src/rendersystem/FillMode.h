/**********************************************************************
*	Filename: FillMode.h
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
#ifndef FILLMODE_H_
#define FILLMODE_H_

struct FillType
{
    enum Enum
    {
        Point = 0,
        Line,
        Fill
    };
};

class FillMode
{
public:
    //!***************************************************************
    //! @details:
    //! constructor
    //!
    //! @note: 
    //! set to Fill by default
    //!***************************************************************
    FillMode();

    //!***************************************************************
    //! @details:
    //! sets the fill type
    //!***************************************************************
    void SetFillType(FillType::Enum type);

    //!***************************************************************
    //! @details:
    //! accessor for the current file type
    //!***************************************************************
    FillType::Enum GetFillType() const;

private:
    FillType::Enum m_fillType;
};

bool operator==(const FillMode& lhs, const FillMode& rhs);
bool operator!=(const FillMode& lhs, const FillMode& rhs);

#endif