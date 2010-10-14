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

#include <vector>

#include "stdint.h"
#include "Color.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Renderable.h"
#include "Vertex.h"
#include "Rect.h"
#include "Entity.h"

class SceneManager;
class BillboardGroup;

class Billboard : public Renderable, public Entity
{
public:
    Billboard(SceneManager* sceneManager);
    Billboard(SceneManager* sceneManager, const Vector3& position);
    Billboard(SceneManager* sceneManager, BillboardGroup* owner, const Vector3& position = Vector3::Zero());

    void SetDimensions(uint32_t width, uint32_t height);
    void SetWidth(uint32_t width);
    void SetHeight(uint32_t height);
    uint32_t GetWidth(uint32_t width) const;
    uint32_t GetHeight(uint32_t height) const;

    void SetPosition(const Vector3& position);
    const Vector3& GetPosition() const;

    void SetColor(const Color& color);
    const Color& GetColor() const;

    void SetTextureCoordinates(const FloatRect& texCoords);
    void SetTextureCoordinates(float left, float top, float right, float bottom);
    const FloatRect& GetTextureCoordinates() const;

    uint32_t GetNumberOfVertices() const;
    
    virtual Renderable* GetRenderable();
    virtual void Update(uint32_t time);

private:
    void GenerateBuffers();
    void GenerateIndices();

private:
    SceneManager* m_sceneManager;
    BillboardGroup* m_owner;
    uint32_t m_width;
    uint32_t m_height;
    Vector3 m_position;
    Color m_color;
    FloatRect m_textureCoords;
    std::vector<Vertex> m_vertices;
    bool m_buffersGenerated;
};

#endif
