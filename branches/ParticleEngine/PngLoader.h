
#ifndef PNG_LOADER_H_
#define PNG_LOADER_H_

#include <istream>

class Image;

class PngLoader
{
public:
	bool IsLoadable(std::istream& source);
	Image* Load(const char* filename);
};

#endif

