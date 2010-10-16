/**********************************************************************
*	Filename: ISpriteSheet.h
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
#ifndef ISPRITESHEET_H_
#define ISPRITESHEET_H_

#include "stdint.h"
#include "Dimension.h"
#include "Rect.h"

class Image;
class ITexture;

struct StorageType
{
    enum Enum
    {
        RowMajor = 0,
        ColMajor
    };
};

class ISpriteSheet
{
public:

    virtual ~ISpriteSheet() { };

    virtual Image* GetImage() const = 0;
    virtual ITexture* GetTexture() const = 0;

    virtual void SetNumTiles(uint32_t numTiles) = 0;
    virtual uint32_t GetNumTiles() const = 0;

    virtual void SetNumRows(uint32_t numRows) = 0;
    virtual uint32_t GetNumRows() const = 0;

    virtual void SetNumCols(uint32_t numCols) = 0;
    virtual uint32_t GetNumCols() const = 0;

    virtual FloatRect GetTileCoords(uint32_t index) const = 0;
};

#endif