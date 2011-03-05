/**********************************************************************
*	Filename: Path.h
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
#ifndef PATH_H_
#define PATH_H_

#include "../StdIncludes.h"

#include "IPath.h"

namespace filesystem
{
    class Path : public IPath
    {
    public:
        Path(const char* path);
        Path(const std::string& path);
        Path(const Path& rhs);

        virtual std::string GetString() const;
        virtual std::string GetFilename() const;
        virtual std::string GetExtension() const;
        virtual bool HasExtension() const;
        virtual void ReplaceExtension(const std::string& extension);
        virtual void Append(const std::string& path);
        virtual void Append(const IPath& path);

        Path& operator/=(const std::string& path);
        Path& operator/=(const IPath& path);

    private:
        std::string& GetStringRef() const;

    private:
        std::string m_origPath;

        // making these mutable so they can be set
        // in const functions, makes it convenient to 
        // keep track of when updates should happen
        mutable bool m_updatePlatformSpecific;
        mutable std::string m_platformSpecificPath;
    };
}

#endif
