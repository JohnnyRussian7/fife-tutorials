/**********************************************************************
 *	Filename: DepthBufferWriteMode.h
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
#ifndef DEPTHBUFFERWRITEMODE_H_
#define DEPTHBUFFERWRITEMODE_H_

class DepthBufferWriteMode
{
public:
    //**********************************************************************
    //! @details
    //! constructor
    //!
    //! @note
    //! defaults to enabled
    //**********************************************************************
    DepthBufferWriteMode();
    
    //**********************************************************************
    //! @details
    //! sets whether depth buffer writing is enabled or not
    //**********************************************************************
    void SetEnabled(bool enabled);
    
    //**********************************************************************
    //! @details
    //! accessor for whether depth buffer writing is enabled
    //**********************************************************************
    bool IsEnabled() const;
    
private:
    bool m_enabled;
};

bool operator==(const DepthBufferWriteMode& lhs, const DepthBufferWriteMode& rhs);
bool operator!=(const DepthBufferWriteMode& lhs, const DepthBufferWriteMode& rhs);

#endif

