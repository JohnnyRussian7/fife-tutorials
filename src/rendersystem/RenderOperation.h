/**********************************************************************
*	Filename: RenderOperation.h
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
#ifndef RENDEROPERATION_H_
#define RENDEROPERATION_H_

#include "graphics/BlendingMode.h"

class Renderable;

class RenderOperation
{
public:
    //**********************************************************************
    //! @details
    //! constructor
    //**********************************************************************
    RenderOperation();

    //**********************************************************************
    //! @details
    //! destructor
    //**********************************************************************
    ~RenderOperation();

    //**********************************************************************
    //! @details
    //! sets the renderable for this render operation
    //**********************************************************************
    void SetRenderable(Renderable* renderable);

    //**********************************************************************
    //! @details
    //! accessor for the renderable stored in this render operation
    //**********************************************************************
    Renderable* GetRenderable() const;

    //**********************************************************************
    //! @details
    //! sets the blending mode for this render operation
    //**********************************************************************
    void SetBlendingMode(const BlendingMode& blendingMode);

    //**********************************************************************
    //! @details
    //! accessor for the blending mode set for this render operation
    //**********************************************************************
    const BlendingMode& GetBlendingMode() const;

private:
    Renderable* m_renderable;
    BlendingMode m_blendingMode;
};

#endif
