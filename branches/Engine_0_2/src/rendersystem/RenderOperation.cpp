/**********************************************************************
*	Filename: RenderOperation.cpp
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
#include "PrecompiledIncludes.h"

#include "RenderOperation.h"

RenderOperation::RenderOperation()
{

}

RenderOperation::~RenderOperation()
{

}

void RenderOperation::SetRenderable(Renderable* renderable)
{
    m_renderable = renderable;
}

Renderable* RenderOperation::GetRenderable() const
{
    return m_renderable;
}

void RenderOperation::SetBlendingMode(const BlendingMode& blendingMode)
{
    m_blendingMode = blendingMode;
}

const BlendingMode& RenderOperation::GetBlendingMode() const
{
    return m_blendingMode;
}

void RenderOperation::SetCullMode(const CullMode& cullMode)
{
    m_cullMode = cullMode;
}

const CullMode& RenderOperation::GetCullMode() const
{
    return m_cullMode;
}

void RenderOperation::SetPolygonWindingMode(const PolygonWindingMode& windingMode)
{
    m_windingMode = windingMode;
}

const PolygonWindingMode& RenderOperation::GetPolygonWindingMode() const
{
    return m_windingMode;
}