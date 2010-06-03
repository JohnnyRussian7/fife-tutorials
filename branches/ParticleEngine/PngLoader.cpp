
#include "PngLoader.h"
#include "libpng/png.h"

#include <fstream>

const int PNG_SIG_SIZE = 8;

static void png_error(png_structp pngPtr, png_const_charp msg)
{
	longjmp(pngPtr->jmpbuf, 1);
}

void PNGAPI userReadData(png_structp pngPtr, png_bytep data, png_size_t length)
{
	// get io pointer from read struct and cast to istream 
	std::istream* file = (std::ifstream*)png_get_io_ptr(pngPtr);
	
	// read length amount into data
	file->read((char*)data,length);
	png_size_t numRead = file->gcount();

	if (numRead != length)
	{
		png_error(pngPtr, "Read Error");
	}
}

bool PngLoader::isLoadable(std::istream& source)
{
	png_byte pngsig[PNG_SIG_SIZE];

	source.read((char*)pngsig, PNG_SIG_SIZE);

	if (!source.good())
	{
		return false;
	}

	int isLoadable = png_sig_cmp(pngsig, 0, PNG_SIG_SIZE);

	return (isLoadable == 0);
}

void PngLoader::load(const char* filename)
{
	if (!filename)
	{
		//return 0;
	}

	std::ifstream file(filename);
	if (!file || !isLoadable(file))
	{
		//return 0;
	}

	// create read struct
	png_structp pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, (png_error_ptr)png_error, NULL);
	if (!pngPtr)
	{
		//return 0;
	}

	png_infop infoPtr = png_create_info_struct(pngPtr);
	if (!infoPtr)
	{
		// destroy read structure created above
		png_destroy_read_struct(&pngPtr, NULL, NULL);

		//return 0;
	}

	png_bytep* rowPtrs = NULL;
	char* data = NULL;

	if (setjmp(png_jmpbuf(pngPtr)))
	{
		// error occured during parsing need to clean up
		png_destroy_read_struct(&pngPtr, &infoPtr, NULL);
		
		if (rowPtrs)
		{
			delete [] rowPtrs;
			rowPtrs = NULL;
		}

		if (data)
		{
			delete data;
			data = NULL;
		}

		//return 0;
	}

	// setup custom read function
	png_set_read_fn(pngPtr, &file, userReadData);

	// tell libpng we have already read the signature
	png_set_sig_bytes(pngPtr, PNG_SIG_SIZE);

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

}