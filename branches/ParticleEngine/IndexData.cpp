/**********************************************************************
*	Filename: IndexData.cpp
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

#include "IndexData.h"

IndexData::IndexData()
{

}

IndexData::IndexData(uint32_t numIndices)
: m_indices(numIndices, 0.f)
{

}

IndexData::IndexData(float* indices, uint32_t numIndices)
{
	m_indices.reserve(numIndices);

	AddIndices(indices, numIndices);
}

void IndexData::AddIndex(float index)
{
	m_indices.push_back(index);
}

void IndexData::AddIndices(float* indices, uint32_t numIndices)
{
	for (uint32_t i=0; i < numIndices; ++i)
	{
		m_indices.push_back(indices[i]);
	}
}

void IndexData::Clear()
{
	// remove all Indices
	m_indices.clear();

	// shrink index container
	IndexContainer().swap(m_indices);
}

float* IndexData::GetIndices()
{
	if (!m_indices.empty())
	{
		return &m_indices[0];
	}

	return 0;
}

uint32_t IndexData::GetNumIndices() const
{
	return m_indices.size();
}