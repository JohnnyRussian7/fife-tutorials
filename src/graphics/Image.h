/**********************************************************************
*	Filename: Image.h
*	
*	Copyright (C) 2011, FIFE team
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
#ifndef IMAGE_H_
#define IMAGE_H_

#include "../StdIncludes.h"
#include "IImage.h"

class Image : public IImage
{
public:
	Image(ColorFormat::Enum format, uint32_t width, uint32_t height, const char* name=0);
	Image(const Image& rhs);
	~Image();

    virtual const char* GetName() const;
	virtual uint32_t GetWidth() const;
	virtual uint32_t GetHeight() const;
	virtual uint32_t GetStride() const;
	virtual ColorFormat::Enum GetColorFormat() const;

	virtual uint8_t* GetData();
    virtual uint32_t GetDataSize() const;

private:
    std::string m_name;
	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_stride;
	ColorFormat::Enum m_colorFormat;

	uint8_t* m_data;
};

#endif
