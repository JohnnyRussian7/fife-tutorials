/**********************************************************************
*	Filename: IImageLoader.h
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
#ifndef IIMAGELOADER_H_
#define IIMAGELOADER_H_

class IImage;

namespace filesystem {
    class IPath;
}

namespace graphics
{
    class IImageLoader
    {
    public:
        virtual ~IImageLoader() { };

        virtual bool IsLoadable(const filesystem::IPath& file) = 0;
        virtual IImage* Load(const filesystem::IPath& file) = 0;
        virtual IImage* Load(const std::string& file) = 0;
        virtual IImage* Load(const char* file) = 0;
    };

    IImageLoader* CreateImageLoader(const std::string& type);
}

#endif
