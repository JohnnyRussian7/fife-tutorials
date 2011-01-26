/**********************************************************************
*	Filename: BillboardGroup.h
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
#ifndef BILLBOARDGROUP_H_
#define BILLBOARDGROUP_H_

#include "../StdIncludes.h"

#include "../math/Vector3.h"

class VertexData;
class IndexData;

class BillboardGroup
{
public:
	BillboardGroup(uint32_t numBillboards = 0);

    void SetNumberOfBillboards(uint32_t numBillboards);
    uint32_t GetNumberOfBillboards() const;

	void SetPosition(uint32_t billBoardIndex, const Vector3& position);
	const Vector3& GetPosition(uint32_t billBoardIndex) const;

private:
    uint32_t m_numBillboards;
	std::vector<Vector3> m_position;
    VertexData* m_vertexData;
    IndexData* m_indexData;
};

#endif