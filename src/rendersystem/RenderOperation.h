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

#include "BlendingMode.h"
#include "CullMode.h"
#include "PolygonWindingMode.h"
#include "FillMode.h"
#include "AlphaTestMode.h"

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

    //!***************************************************************
    //! @details:
    //! sets the cull mode for this render operation
    //!***************************************************************
    void SetCullMode(const CullMode& cullMode);

    //!***************************************************************
    //! @details:
    //! accessor for the cull mode set for this render operation
    //!***************************************************************
    const CullMode& GetCullMode() const;

    //!***************************************************************
    //! @details:
    //! sets the winding mode for this render operation
    //!***************************************************************
    void SetPolygonWindingMode(const PolygonWindingMode& windingMode);

    //!***************************************************************
    //! @details:
    //! accessor for the winding mode set for this render operation
    //!***************************************************************
    const PolygonWindingMode& GetPolygonWindingMode() const; 

    //!***************************************************************
    //! @details:
    //! sets the fill mode for this render operation
    //!***************************************************************
    void SetFillMode(const FillMode& fillMode);

    //!***************************************************************
    //! @details:
    //! accessor for the fill mode for this render operation
    //!***************************************************************
    const FillMode& GetFillMode() const;

    //!***************************************************************
    //! @details:
    //! sets the alpha test mode for this render operation
    //!***************************************************************
    void SetAlphaTestMode(const AlphaTestMode& alphaTestMode);

    //!***************************************************************
    //! @details:
    //! accessor for the alpha test mode for this render operation
    //!***************************************************************
    const AlphaTestMode& GetAlphaTestMode() const;

private:
    Renderable* m_renderable;
    BlendingMode m_blendingMode;
    CullMode m_cullMode;
    PolygonWindingMode m_windingMode;
    FillMode m_fillMode;
    AlphaTestMode m_alphaTestMode;
};

#endif
