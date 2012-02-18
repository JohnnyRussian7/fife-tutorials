/**********************************************************************
*	Filename: Billboard.h
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
#ifndef BILLBOARD_H_
#define BILLBOARD_H_

#include "../StdIncludes.h"

#include "Renderable.h"
#include "../Entity.h"
#include "../Visual.h"
#include "../Color.h"
#include "../math/Vector3.h"
#include "../graphics/Vertex.h"
#include "../graphics/VertexData.h"
#include "../geometry/Rect.h"

class SceneManager;
class BillboardGroup;
class IndexData;

class Billboard : public Visual
{
public:
    Billboard(BillboardGroup* parent=0, uint32_t width=1, uint32_t height=1, const Vector3& position=Vector3::Zero());
    Billboard(SceneManager* sceneManager);
    Billboard(SceneManager* sceneManager, const Vector3& position);
    Billboard(SceneManager* sceneManager, BillboardGroup* owner, const Vector3& position = Vector3::Zero());

    void InitIndices();
    
    void SetDimensions(uint32_t width, uint32_t height);
    void SetWidth(uint32_t width);
    void SetHeight(uint32_t height);
    uint32_t GetWidth() const;
    uint32_t GetHeight() const;

    void SetPosition(const Vector3& position);
    const Vector3& GetPosition() const;

    void SetColor(const Color& color);
    const Color& GetColor() const;

    void SetTextureCoordinates(const FloatRect& texCoords);
    void SetTextureCoordinates(float left, float top, float right, float bottom);
    const FloatRect& GetTextureCoordinates() const;

    void FillVertexData(VertexData& vertexData);
    void FillIndexData(IndexData& indexData, uint32_t billboardNumber);
    
    virtual Renderable* GetRenderable();
    virtual void Update(uint32_t time);

    // static helper methods
    static uint32_t GetNumberOfVertices();
    static uint32_t GetNumberOfIndices();

private:
    void MarkDirty();
    void ResetDirty();
    bool IsDirty() const;
    void Update();

    // TODO - do these need to be here anymore
    void GenerateBuffers();
    void UpdateBuffers();

private:
    SceneManager* m_sceneManager;
    BillboardGroup* m_parent;
    bool m_dirty;
    uint32_t m_width;
    uint32_t m_height;
    Vector3 m_position;
    Color m_color;
    FloatRect m_textureCoords;
    VertexData m_vertexData;

    std::vector<uint16_t> m_indices;
    
    // TODO - these can be removed when GenerateBuffers and UpdateBuffers are removed
    std::vector<Vertex> m_vertices;
    bool m_buffersGenerated;
};

#endif
