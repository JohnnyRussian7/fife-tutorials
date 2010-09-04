/**********************************************************************
*	Filename: BillboardGroup.cpp
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

#include "BillboardGroup.h"
#include "VertexData.h"
#include "IndexData.h"

BillboardGroup::BillboardGroup(uint32_t numBillboards)
: m_numBillboards(numBillboards), m_vertexData(new VertexData()), m_indexData(new IndexData())
{

}

void BillboardGroup::SetNumberOfBillboards(uint32_t numBillboards)
{
    m_numBillboards = numBillboards;
}

uint32_t BillboardGroup::GetNumberOfBillboards() const
{
    return m_numBillboards;
}

void BillboardGroup::SetPosition(uint32_t billBoardIndex, const Vector3& position)
{
    if (billBoardIndex < m_position.size())
    {
        m_position[billBoardIndex] = position;
    }
}

const Vector3& BillboardGroup::GetPosition(uint32_t billBoardIndex) const
{
    return m_position[billBoardIndex];
}