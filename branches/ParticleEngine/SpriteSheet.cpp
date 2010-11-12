/**********************************************************************
*	Filename: SpriteSheet.cpp
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

#include <cassert>

#include "SpriteSheet.h"
#include "Image.h"
#include "OpenglTexture.h"

SpriteSheet::SpriteSheet(Image* image)
: m_image(image), m_texture(), m_numTiles(0), m_numRows(0), m_numCols(0), m_tileSize(0, 0),
  m_storageType(StorageType::RowMajor)
{
    assert(m_image);
}

SpriteSheet::~SpriteSheet()
{

}

Image* SpriteSheet::GetImage() const
{
    return m_image;
}

void SpriteSheet::SetNumTiles(uint32_t numTiles)
{
    m_numTiles = numTiles;
}

uint32_t SpriteSheet::GetNumTiles() const
{
    return m_numTiles;
}

void SpriteSheet::SetNumRows(uint32_t numRows)
{
    m_numRows = numRows;
}

uint32_t SpriteSheet::GetNumRows() const
{
    return m_numRows;
}

void SpriteSheet::SetNumCols(uint32_t numCols)
{
    m_numCols = numCols;
}

uint32_t SpriteSheet::GetNumCols() const
{
    return m_numCols;
}

FloatRect SpriteSheet::GetTileCoords(uint32_t index) const
{
    if (index >= GetNumTiles())
    {
        return FloatRect();
    }

    // calculate row and column
    uint32_t row = 0;
    uint32_t col = 0;
    if (m_storageType == StorageType::ColMajor)
    {
        row = index % m_numRows;
        col = index / m_numRows;
    }
    else
    {
        row = index / m_numCols;
        col = index % m_numCols;
    }

    floatDimension cellSize(1.f/GetNumCols(), 1.f/GetNumRows());

    // calculate uv coordinates based on row and col
    FloatRect rect;
    rect.m_left = col * cellSize.m_width;
    rect.m_top = 1.f - (row * cellSize.m_height);
    rect.m_right = col * cellSize.m_width + cellSize.m_width;
    rect.m_bottom = 1.f - (row * cellSize.m_height + cellSize.m_height);

    return rect;
}