/**********************************************************************
*	Filename: Path.cpp
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

#include "Path.h"
#include "FileSystemUtils.h"

namespace filesystem
{
    Path::Path(const char* path)
    : m_origPath(""), m_updatePlatformSpecific(true), m_platformSpecificPath("")
    {
        assert(path);

        if (path)
        {
            m_origPath = std::string(path);
        }
    }

    Path::Path(const std::string& path)
    : m_origPath(path), m_updatePlatformSpecific(true), m_platformSpecificPath("")
    {

    }

    Path::Path(const Path& rhs)
    : m_origPath(rhs.m_origPath), m_updatePlatformSpecific(true)
    {

    }

    std::string Path::GetString() const
    {
        if (m_updatePlatformSpecific)
        {
            m_platformSpecificPath = filesystem::GetPlatformSpecificString(m_origPath);
            m_updatePlatformSpecific = false;
        }

        return m_platformSpecificPath;
    }

    std::string Path::GetFilename() const
    {
        return filesystem::GetFilename(*this);
    }

    std::string Path::GetExtension() const
    {
        return filesystem::GetExtension(*this);
    }

    bool Path::HasExtension() const
    {
        return (!filesystem::GetExtension(*this).empty());
    }

    void Path::ReplaceExtension(const std::string& extension)
    {
        filesystem::ReplaceExtension(GetStringRef(), extension);

        // set to true here just in case the user decides to
        // replace the extension with a platform specific path
        // plus new extension
        m_updatePlatformSpecific = true;
    }

    void Path::Append(const std::string& path)
    {
        m_origPath += path;
        m_updatePlatformSpecific = true;
    }

    void Path::Append(const IPath& path)
    {
        m_origPath += path.GetString();

        // append directly here since GetString will convert
        // the path to platform specific
        m_platformSpecificPath += path.GetString();
    }

    Path& Path::operator/=(const std::string& path)
    {
        m_origPath = m_origPath + filesystem::FileSeparator + path;
        m_updatePlatformSpecific = true;

        return *this;
    }

    Path& Path::operator/=(const IPath& path)
    {
        m_origPath += path.GetString();

        // append directly here since GetString will convert
        // the path to platform specific
        m_platformSpecificPath += path.GetString();

        return *this;
    }

    std::string& Path::GetStringRef() const
    {
        if (m_updatePlatformSpecific)
        {
            m_platformSpecificPath = filesystem::GetPlatformSpecificString(m_origPath);
            m_updatePlatformSpecific = false;
        }

        return m_platformSpecificPath;
    }
}
