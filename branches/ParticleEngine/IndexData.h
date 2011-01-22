/**********************************************************************
*	Filename: IndexData.h
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
#ifndef INDEXDATA_H_
#define INDEXDATA_H_

#include "StdIncludes.h"

class IndexData
{
public:
	IndexData();
	IndexData(uint32_t numIndices);
	IndexData(float* indices, uint32_t numIndices);

	void AddIndex(float index);
	void AddIndices(float* indices, uint32_t numIndices);
	void Clear();
	float* GetIndices();
	uint32_t GetNumIndices() const;
	
private:
	typedef std::vector<float> IndexContainer;
	IndexContainer m_indices;
};

#endif
