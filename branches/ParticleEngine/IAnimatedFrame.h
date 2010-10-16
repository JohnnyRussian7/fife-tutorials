/**********************************************************************
*	Filename: IAnimatedFrame.h
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
#ifndef IANIMATEDFRAME_H_
#define IANIMATEDFRAME_H_

template <typename T> struct Rect;
class ITexture;

class IAnimatedFrame
{
public:
    virtual ~IAnimatedFrame() { };

    virtual const char* GetName() const = 0;
    virtual uint32_t GetFrameNumber() const = 0;
    virtual void SetTexture(ITexture* texture) = 0;
    virtual ITexture* GetTexture() const = 0;
    virtual const FloatRect& GetTextureCoordinates() const = 0;
    virtual void SetTextureCoordinates(const FloatRect& texCoords) = 0;
    virtual void SetTextureCoordinates(float left, float top, float right, float bottom) = 0;
};

#endif
