/**********************************************************************
*	Filename: VertexData.h
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
#ifndef VERTEXDATA_H_
#define VERTEXDATA_H_

#include  <vector>

#include "Vertex.h"
#include "stdint.h"

class VertexData
{
public:
	VertexData();
	VertexData(uint32_t numVertices);
	VertexData(const Vertex* vertices, uint32_t numVertices);

	void AddVertex(const Vertex& vertex);
	void AddVertices(const Vertex* vertices, uint32_t numVertices);
	void Clear();
	Vertex* GetVertices();
	uint32_t GetNumVertices() const;

private:
	typedef std::vector<Vertex> VertexContainer;
	VertexContainer m_vertices;
};

#endif
