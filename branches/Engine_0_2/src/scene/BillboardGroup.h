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

#include "Billboard.h"
#include "../graphics/VertexData.h"
#include "../graphics/IndexData.h"
#include "../Color.h"
#include "../math/Vector3.h"
#include "../geometry/Rect.h"

class SceneManager;

class BillboardGroup
{
public:
	BillboardGroup(SceneManager* sceneManager, uint32_t numBillboards = 0, uint32_t width=1, uint32_t height=1, const FloatRect& textureCoordinates=FloatRect(0, 1, 1, 0));

    void SetNumberOfBillboards(uint32_t numBillboards);
    uint32_t GetNumberOfBillboards() const;

    void SetPosition(uint32_t index, const Vector3& position);
    Vector3 GetPosition(uint32_t index) const;

    void SetWidth(uint32_t index, uint32_t width);
    uint32_t GetWidth(uint32_t index) const;

    void SetHeight(uint32_t index, uint32_t height);
    uint32_t GetHeight(uint32_t index) const;

    void SetColor(uint32_t index, const Color& color);
    Color GetColor(uint32_t index) const;

    void SetTextureCoordinates(uint32_t index, const FloatRect& texCoords);
    FloatRect GetTextureCoordinates(uint32_t index) const;

    VertexData& GetVertexData();
    IndexData& GetIndexData();

private:
    void MarkDirty();
    void ResetDirty();
    bool IsDirty() const;
    void UpdateBuffers();

private:
    SceneManager* m_sceneManager;
    bool m_dirty;
    uint32_t m_numBillboards;
    uint32_t m_width;
    uint32_t m_height;
    FloatRect m_textureCoordinates;

    typedef std::vector<Billboard> BillboardContainer;
    BillboardContainer m_billBoards;

    VertexData m_vertexData;
    IndexData m_indexData;
};

#endif