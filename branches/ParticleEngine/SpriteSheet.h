/**********************************************************************
*	Filename: SpriteSheet.h
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
#ifndef SPRITESHEET_H_
#define SPRITESHEET_H_

#include "StdIncludes.h"

#include "ISpriteSheet.h"
#include "Dimension.h"
#include "Rect.h"

class Image;

class SpriteSheet : public ISpriteSheet
{
public:
    SpriteSheet(Image* image);
    ~SpriteSheet();

    virtual Image* GetImage() const;

    virtual void SetNumTiles(uint32_t numTiles);
    virtual uint32_t GetNumTiles() const;

    virtual void SetNumRows(uint32_t numRows);
    virtual uint32_t GetNumRows() const;

    virtual void SetNumCols(uint32_t numCols);
    virtual uint32_t GetNumCols() const;

    virtual FloatRect GetTileCoords(uint32_t index) const;

private:
    Image* m_image;
    uint32_t m_numTiles;
    uint32_t m_numRows;
    uint32_t m_numCols;
    floatDimension m_tileSize;
    StorageType::Enum m_storageType;
};

#endif
