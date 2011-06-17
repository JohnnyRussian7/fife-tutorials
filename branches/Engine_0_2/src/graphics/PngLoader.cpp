/**********************************************************************
*	Filename: PngLoader.cpp
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

#include "PngLoader.h"
#include "IImage.h"
#include "Image.h"     // TODO - this may not need to be here forever
#include "../filesystem/IPath.h"
#include "../filesystem/Path.h"

#include "../../extern/libpng/png.h"

namespace
{
    const int PngSignatureSizeInBytes = 8;
}

void png_error_fn(png_structp pngPtr, png_const_charp /*msg*/)
{
	longjmp(pngPtr->jmpbuf, 1);
}

void PNGAPI userReadData(png_structp pngPtr, png_bytep data, png_size_t length)
{
	// get io pointer from read struct and cast to istream 
	std::istream* file = (std::istream*)png_get_io_ptr(pngPtr);
	
	// read length amount into data
	file->read((char*)data,length);
	png_size_t numRead = file->gcount();

	if (numRead != length)
	{
		png_error_fn(pngPtr, "Read Error");
	}
}

namespace graphics
{
    PngLoader::PngLoader()
    {

    }

    bool PngLoader::IsLoadable(const filesystem::IPath& file)
    {
        std::ifstream source(file.GetString().c_str(), std::ios::binary);

        if (!source)
        {
            return false;
        }

	    png_byte pngsig[PngSignatureSizeInBytes];

	    source.read((char*)pngsig, PngSignatureSizeInBytes);

	    if (source.gcount() != PngSignatureSizeInBytes)
	    {
		    return false;
	    }

	    return !png_sig_cmp(pngsig, 0, PngSignatureSizeInBytes);
    }

    IImage* PngLoader::Load(const filesystem::IPath& file, const char* name)
    {
        if (!IsLoadable(file))
        {
            return 0;
        }

        std::ifstream source(file.GetString().c_str(), std::ios::binary);

        // create read struct
        png_structp pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, (png_error_ptr)png_error_fn, NULL);
        if (!pngPtr)
        {
            return 0;
        }

        png_infop infoPtr = png_create_info_struct(pngPtr);
        if (!infoPtr)
        {
            // destroy read structure created above
            png_destroy_read_struct(&pngPtr, NULL, NULL);

            return 0;
        }

        png_bytep* rowPtrs = NULL;

        if (setjmp(png_jmpbuf(pngPtr)))
        {
            // error occurred during parsing need to clean up
            png_destroy_read_struct(&pngPtr, &infoPtr, NULL);

            if (rowPtrs)
            {
                delete [] rowPtrs;
                rowPtrs = NULL;
            }

            return 0;
        }

        // setup custom read function
        png_set_read_fn(pngPtr, &source, userReadData);

        // get png file info
        png_read_info(pngPtr, infoPtr);

        png_uint_32 width = png_get_image_width(pngPtr, infoPtr);
        png_uint_32 height = png_get_image_height(pngPtr, infoPtr);
        png_uint_32 bitDepth = png_get_bit_depth(pngPtr, infoPtr);
        png_uint_32 channels = png_get_channels(pngPtr, infoPtr);
        png_uint_32 colorType = png_get_color_type(pngPtr, infoPtr);

        switch (colorType)
        {
        case PNG_COLOR_TYPE_PALETTE:
            {
                png_set_palette_to_rgb(pngPtr);
            }
            break;
        case PNG_COLOR_TYPE_GRAY:
        case PNG_COLOR_TYPE_GRAY_ALPHA:
            {
                if (bitDepth < 8)
                {
                    png_set_expand_gray_1_2_4_to_8(pngPtr);
                }
                else
                {
                    png_set_packing(pngPtr);
                }

                png_set_gray_to_rgb(pngPtr);
            }
            break;
        }

        if (png_get_valid(pngPtr, infoPtr, PNG_INFO_tRNS))
        {
            png_set_tRNS_to_alpha(pngPtr);
        }

        if (bitDepth == 16)
        {
            png_set_strip_16(pngPtr);
        }

        // read updated info after changes above
        png_read_update_info(pngPtr, infoPtr);

        width = png_get_image_width(pngPtr, infoPtr);
        height = png_get_image_height(pngPtr, infoPtr);
        bitDepth = png_get_bit_depth(pngPtr, infoPtr);
        channels = png_get_channels(pngPtr, infoPtr);
        colorType = png_get_color_type(pngPtr, infoPtr);

        ColorFormat::Enum colorFormat = ColorFormat::R8G8B8A8;
        if (colorType == PNG_COLOR_TYPE_RGB)
        {
            colorFormat = ColorFormat::R8G8B8;
        }

        // create image object
        IImage* img = new Image(colorFormat, width, height, name);

        // assign image data to row pointers for reading
        rowPtrs = new png_bytep[height];
        uint8_t* data = img->GetData();
        for (std::size_t i=0; i < height; ++i)
        {
            rowPtrs[height-i-1] = (png_bytep)data + i*img->GetStride();
        }

        // read image data
        png_read_image(pngPtr, rowPtrs);

        //png_read_end(pngPtr, NULL);

        delete [] rowPtrs;

        png_destroy_read_struct(&pngPtr, &infoPtr, NULL);

        return img;
    }

    IImage* PngLoader::Load(const std::string& file, const char* name)
    {      
        return Load(filesystem::Path(file), name);
    }

    IImage* PngLoader::Load(const char* file, const char* name)
    {
	    if (!file)
	    {
		    return 0;
	    }

        return Load(filesystem::Path(file), name);
    }
}