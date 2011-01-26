/**********************************************************************
*	Filename: Image.cpp
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
#include "PrecompiledIncludes.h"

#include "Image.h"

Image::Image(ColorFormat::Enum format, uint32_t width, uint32_t height)
: m_width(width), m_height(height), 
  m_bytesPerPixel(ColorFormat::GetBitsPerPixel(format)/8), m_colorFormat(format)
{
	m_stride = m_width * m_bytesPerPixel;

	m_data = new uint8_t[m_width*m_stride];
}

Image::Image(const Image& rhs)
: m_width(rhs.m_width), m_height(rhs.m_height), m_bytesPerPixel(rhs.m_bytesPerPixel),
  m_colorFormat(rhs.m_colorFormat), m_stride(rhs.m_stride)
{
	m_data = new uint8_t[m_width*m_stride];
	memcpy(m_data, rhs.m_data, sizeof(m_width*m_stride));
}

Image::~Image()
{
	delete [] m_data;
	m_data = 0;
}

uint32_t Image::GetWidth() const
{
	return m_width;
}

uint32_t Image::GetHeight() const
{
	return m_height;
}

uint32_t Image::GetStride() const
{
	return m_stride;
}

ColorFormat::Enum Image::GetColorFormat() const
{
	return m_colorFormat;
}

uint8_t* Image::GetData()
{
	return m_data;
}

uint32_t Image::GetDataSize() const
{
    return m_width*m_stride;
}