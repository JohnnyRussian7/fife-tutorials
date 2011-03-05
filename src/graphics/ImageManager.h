/**********************************************************************
*	Filename: ImageManager.h
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
#ifndef IMAGEMANAGER_H_
#define IMAGEMANAGER_H_

#include "ImageFwd.h"
#include "ImageEnums.h"

namespace filesystem {
    class IPath;
}

class ImageManager
{
public:
    ImageManager();

    ImagePtr CreateImage(const filesystem::IPath& path, /*IImageLoader* loader=0,*/const char* name=0);
    ImagePtr CreateImage(const std::string& file, /*IImageLoader* loader=0,*/ const char* name=0);
    bool AddImage(IImage* image);
    void RemoveImage(IImage* image);
    void RemoveImage(const char* name);
    void RemoveAllImages();
    void RemoveUnusedImages();

private:
    typedef std::map<std::string, ImagePtr> ImageContainer;
    ImageContainer m_images;
};

#endif
