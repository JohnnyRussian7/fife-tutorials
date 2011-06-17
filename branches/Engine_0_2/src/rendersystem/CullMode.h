/**********************************************************************
*	Filename: CullMode.h
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
#ifndef CULLMODE_H_
#define CULLMODE_H_

struct CullType
{
    enum Enum
    {
        Front = 0,
        Back,
        Both
    };
};

class CullMode
{
public:
    //!***************************************************************
    //! @details:
    //! constructor
    //!
    //! @note
    //! disabled by default
    //!***************************************************************
    CullMode();

    //!***************************************************************
    //! @details:
    //! set whether culling is enabled or disabled
    //!***************************************************************
    void SetEnabled(bool enabled);

    //!***************************************************************
    //! @details:
    //! accessor for whether culling is enabled
    //!***************************************************************
    bool IsEnabled() const;

    //!***************************************************************
    //! @details:
    //! sets the culling mode type
    //!***************************************************************
    void SetCullType(CullType::Enum cullType);

    //!***************************************************************
    //! @details:
    //! accessor for the cull type that is currently set
    //!***************************************************************
    CullType::Enum GetCullType() const;

private:
    bool m_enabled;
    CullType::Enum m_cullType;
};

bool operator==(const CullMode& lhs, const CullMode& rhs);
bool operator!=(const CullMode& lhs, const CullMode& rhs);

#endif
