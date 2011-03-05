/**********************************************************************
*	Filename: IPath.h
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
#ifndef IPATH_H_
#define IPATH_H_

namespace filesystem
{
    class IPath
    {
    public:
        virtual ~IPath() { };

        virtual std::string GetString() const = 0;
        virtual std::string GetFilename() const = 0;
        virtual std::string GetExtension() const = 0;
        virtual bool HasExtension() const = 0;
        virtual void ReplaceExtension(const std::string& extension) = 0;
        virtual void Append(const std::string& path) = 0;
        virtual void Append(const IPath& path) = 0;
        virtual IPath& operator/=(const std::string& path) = 0;
        virtual IPath& operator/=(const IPath& path) = 0;
    };
}

#endif
