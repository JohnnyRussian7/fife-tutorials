/**********************************************************************
*	Filename: CheckedCast.h
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
#ifndef CHECKEDCAST_H_
#define CHECKEDCAST_H_

//!***************************************************************
//! @details:
//! utility function to provide type safety checks when
//! debugging while skipping the type safety in release mode
//! to provide more efficiency. This is meant to be used
//! when converting from base class to child class within
//! a hierarchy
//!
//! @note
//! _DEBUG must be defined for this function to provide 
//! type safety checks. Also IGNORE_DEBUG can be defined
//! to avoid the type safety checks while in debug mode
//!
//! @param[in]: from
//! the input parameter to convert to the output type
//!
//! @return: 
//! A casted pointer to the output type, or NULL if the
//! conversion fails
//! 
//!***************************************************************
template <typename To, typename From>
To checked_cast(From* from)
{
    if (!from)
    {
        return 0;
    }

#if defined(_DEBUG) && !defined(IGNORE_DEBUG)
    (dynamic_cast<To>(from) !=0 ) ? assert(true) : assert(false);
#endif
    return static_cast<To>(from);
}

#endif