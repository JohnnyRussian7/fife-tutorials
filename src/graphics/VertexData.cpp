/**********************************************************************
*	Filename: VertexData.cpp
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

#include "VertexData.h"


VertexData::VertexData()
{

}

VertexData::VertexData( uint32_t numVertices )
{
    m_vertices.reserve(numVertices);
}

VertexData::VertexData( const Vertex* vertices, uint32_t numVertices )
{
	m_vertices.reserve(numVertices);
	
	AddVertices(vertices, numVertices);
}

void VertexData::AddVertex( const Vertex& vertex )
{
	m_vertices.push_back(vertex);
}

void VertexData::AddVertices( const Vertex* vertices, uint32_t numVertices )
{
    if (m_vertices.size() < numVertices)
    {
        m_vertices.reserve(m_vertices.size()+numVertices);
    }

	for (uint32_t i=0; i < numVertices; ++i)
	{
		m_vertices.push_back(vertices[i]);
	}
}

void VertexData::Clear()
{
	// remove all vertices
	m_vertices.clear();

	// shrink vertex container
	VertexContainer().swap(m_vertices);
}

Vertex* VertexData::GetVertices()
{
	if (!m_vertices.empty())
	{
		return &m_vertices[0];
	}

	return 0;
}

uint32_t VertexData::GetNumVertices() const
{
	return m_vertices.size();
}