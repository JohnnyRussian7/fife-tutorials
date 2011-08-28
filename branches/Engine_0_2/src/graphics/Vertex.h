/**********************************************************************
*	Filename: Vertex.h
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
#ifndef VERTEX_H_
#define VERTEX_H_

#include "../math/Vector3.h"
#include "../math/Vector2.h"
#include "../Color.h"

// struct VertexDataType
// {
//     enum Enum
//     {
//         Position = 0,
//         Normal,
//         Color,
//         TexCoord0,
//         TexCoord1
//     };
// };
// 
// struct VertexDataLayout
// {
//     enum Enum
//     {
//         Unknown = 0,
//         Vtc,
//         Vntc,
//         VtcInterleaved,
//         VntcInterleaved,
//         VtcSeparate,
//         VntcSeparate,
//     };
// };

// make sure Vertex has no extra padding
#pragma pack(push, 1)

// struct VertexData
// {
//     VertexData() : m_data(0)
// };
// 
// struct VertexElement
// {
//     VertexElement();
// 
//     GetSize();
// 
// private:
// 
//     VertexDataType::Enum m_type;
// };

struct Vertex
{
    Vertex() 
    : m_position(Vector3::Zero()), m_normal(Vector3::Zero()), m_color(Color()), m_textureCoords(Vector2::Zero()) 
    { 
    
    }

    Vertex(const Vector3& position, const Vector3& normal, const Color& color, const Vector2& textureCoords)
    : m_position(position), m_normal(normal), m_color(color), m_textureCoords(textureCoords)
    {

    }

    Vertex(float x, float y, float z, float normalX, float normalY, float normalZ, const Color& color, float textureU, float textureV)
    : m_position(x, y, z), m_normal(normalX, normalY, normalZ), m_color(color), m_textureCoords(textureU, textureV)
    {

    }

    Vector3 m_position;
    Vector3 m_normal;
    Color m_color;
    Vector2 m_textureCoords;
};
#pragma pack(pop)

#endif
