/**********************************************************************
*	Filename: Renderable.h
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
#ifndef RENDERABLE_H_
#define RENDERABLE_H_

#include "../rendersystem/RenderEnums.h"

class Visual;
class IVertexBuffer;
class IIndexBuffer;
class IMaterial;
struct Matrix4;

class Renderable
{
public:
    Renderable(Visual* visual=0);
	~Renderable();

    IVertexBuffer* GetVertexBuffer() const;
    void SetVertexBuffer(IVertexBuffer* vertexBuffer);

    IIndexBuffer* GetIndexBuffer() const;
    void SetIndexBuffer(IIndexBuffer* indexBuffer);

    IMaterial* GetMaterial() const;
    void SetMaterial(IMaterial* material);
    
    void SetPrimitiveType(PrimitiveType::Enum type);
    PrimitiveType::Enum GetPrimitiveType() const;

    Matrix4 GetTransform();

protected:
    Visual* m_parent;
    IVertexBuffer* m_vertexBuffer;
    IIndexBuffer* m_indexBuffer;
    IMaterial* m_material;
    PrimitiveType::Enum m_primitiveType;
};

#endif
