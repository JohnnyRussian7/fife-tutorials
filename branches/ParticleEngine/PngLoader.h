
#ifndef PNG_LOADER_H_
#define PNG_LOADER_H_

#include <istream>


class PngLoader
{
public:
	bool isLoadable(std::istream& source);
	void /*Image**/ load(const char* filename);
};

#endif

