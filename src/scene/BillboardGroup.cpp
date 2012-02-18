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
#include "PrecompiledIncludes.h"

#include "BillboardGroup.h"

BillboardGroup::BillboardGroup(uint32_t numBillboards, uint32_t width, uint32_t height, const FloatRect& textureCoordinates)
: m_dirty(true), m_width(width), m_height(height), m_textureCoordinates(textureCoordinates)
{
    SetNumberOfBillboards(numBillboards);
}

void BillboardGroup::SetNumberOfBillboards(uint32_t numBillboards)
{
    if (numBillboards != m_numBillboards)
    {
        // remove current billboards
        m_billBoards.clear();

        // reserve space for billboards
        m_billBoards.reserve(numBillboards);

        Billboard billBoard(this, m_width, m_height);
        billBoard.SetTextureCoordinates(m_textureCoordinates);
        for (uint32_t i=0; i < numBillboards; ++i)
        {
            m_billBoards.push_back(billBoard);
        }

        m_numBillboards = numBillboards;

        MarkDirty();
    }
}

uint32_t BillboardGroup::GetNumberOfBillboards() const
{
    return m_numBillboards;
}

void BillboardGroup::SetPosition(uint32_t index, const Vector3& position)
{
    if (index < m_billBoards.size())
    {
        m_billBoards[index].SetPosition(position);

        MarkDirty();
    }
}

Vector3 BillboardGroup::GetPosition(uint32_t index) const
{
    if (index < m_billBoards.size())
    {
        m_billBoards[index].GetPosition();
    }

    return Vector3::Zero();
}

void BillboardGroup::SetWidth(uint32_t index, uint32_t width)
{
    if (index < m_billBoards.size())
    {
        m_billBoards[index].SetWidth(width);

        MarkDirty();
    }
}

uint32_t BillboardGroup::GetWidth(uint32_t index) const
{
    if (index < m_billBoards.size())
    {
        m_billBoards[index].GetWidth();
    }

    return m_width;
}

void BillboardGroup::SetHeight(uint32_t index, uint32_t height)
{
    if (index < m_billBoards.size())
    {
        m_billBoards[index].SetHeight(height);

        MarkDirty();
    }
}

uint32_t BillboardGroup::GetHeight(uint32_t index) const
{
    if (index < m_billBoards.size())
    {
        m_billBoards[index].GetHeight();
    }

    return m_height;
}

void BillboardGroup::SetColor(uint32_t index, const Color& color)
{
    if (index < m_billBoards.size())
    {
        m_billBoards[index].SetColor(color);

        MarkDirty();
    }
}

Color BillboardGroup::GetColor(uint32_t index) const
{
    if (index < m_billBoards.size())
    {
        return m_billBoards[index].GetColor();
    }
    
    return Color::Black();
}

void BillboardGroup::SetTextureCoordinates(uint32_t index, const FloatRect& texCoords)
{
    if (index < m_billBoards.size())
    {
        m_billBoards[index].SetTextureCoordinates(texCoords);

        MarkDirty();
    }
}

FloatRect BillboardGroup::GetTextureCoordinates(uint32_t index) const
{
    if (index < m_billBoards.size())
    {
        return m_billBoards[index].GetTextureCoordinates();
    }

    return FloatRect(0, 1, 1, 0);
}

VertexData& BillboardGroup::GetVertexData()
{
    if (IsDirty())
    {
        UpdateBuffers();
    }

    return m_vertexData;
}

IndexData& BillboardGroup::GetIndexData()
{
    if (IsDirty())
    {
        UpdateBuffers();
    }

    return m_indexData;
}

void BillboardGroup::MarkDirty()
{
    m_dirty = true;
}

void BillboardGroup::ResetDirty()
{
    m_dirty = false;
}

bool BillboardGroup::IsDirty() const
{
    return m_dirty;
}

void BillboardGroup::UpdateBuffers()
{
    static uint32_t NumIndexPerBillboard = Billboard::GetNumberOfIndices();

    m_vertexData.Clear();
    m_indexData.Clear();

    BillboardContainer::iterator iter;
    for (uint32_t i=0; i < m_billBoards.size(); ++i)
    {
        m_billBoards[i].FillVertexData(m_vertexData);

        for (uint32_t j=0; j < NumIndexPerBillboard; ++j)
        {
            m_indexData.AddIndex(static_cast<uint16_t>(i*NumIndexPerBillboard + j));
        }
    }
    
    // reset dirty flag
    ResetDirty();
}