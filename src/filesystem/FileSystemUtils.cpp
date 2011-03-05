/**********************************************************************
*	Filename: FileSystemUtils.cpp
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

#include "FileSystemUtils.h"
#include "IPath.h"

namespace
{
    // helper to replace forward slashes with backslashes
    struct ForwardSlashPredicate : public std::unary_function<std::string, bool>
    {
        char operator()(const char& c) const
        {
            if (c == '/')
            {
                return '\\';
            }

            return c;
        }
    };

    // helper to replace backslashes with forward slashes
    struct BackSlashPredicate : public std::unary_function<std::string, bool>
    {
        char operator()(const char& c) const
        {
            if (c == '\\')
            {
                return '/';
            }

            return c;
        }
    };
}

namespace filesystem 
{
#if defined(WINDOWS_OS)
    const char FileSeparator = '\\';
#else
    const char FileSeparator = '/';
#endif

    std::string GetPlatformSpecificString(const std::string& srcPath)
    {
        std::string returnValue;
        returnValue.resize(srcPath.size());

        // convert the file separators to OS specific 
#if defined(WINDOWS_OS)
        std::transform(srcPath.begin(), srcPath.end(), returnValue.begin(), ForwardSlashPredicate()); 
#elif (MACOSX_OS) || (LINUX_OS)
        std::transform(srcPath.begin(), srcPath.end(), returnValue.begin(), BackSlashPredicate()); 
#endif

        return returnValue;
    }

    std::string GetExtension(const IPath& path)
    {
        const std::string& pathStr = path.GetString();

        // find the last '.' character
        std::string::size_type pos = pathStr.find_last_of('.');

        // no '.' character found, return empty string
        if (pos == std::string::npos)
        {
            return "";
        }

        // create a substring from the '.' position to the 
        // last character in the string, this will include
        // the '.' character
        return pathStr.substr(pos);
    }

    void ReplaceExtension(std::string& path, const std::string& extension)
    {
        // find the last '.' character
        std::string::size_type pos = path.find_last_of('.');

        if (pos == std::string::npos)
        {
            // no '.' character found, just append new extension
            path += extension;
        }
        else
        {
            // remove from the last '.' character to the end
            // of the string including the '.' character
            path.erase(pos);

            // then append new extension
            path += extension;
        }
    }

    std::string GetFilename(const IPath& path)
    {
        const std::string& pathStr = path.GetString();

        // find the last file separator
        std::string::size_type pos = pathStr.find_last_of(FileSeparator);

        // no file separator file, just return the whole string
        if (pos == std::string::npos)
        {
            return pathStr;
        }

        // increment up 1 to avoid grabbing the slash character
        pos += 1;
        if (pos < pathStr.length())
        {
            // create a substring from the last file separator
            // to the end of the string
            return pathStr.substr(pos);
        }

        // end of string reached, nothing after the
        // file separator return empty string
        return "";
    }

    std::string GetParentPath(const IPath& path)
    {
        const std::string& pathStr = path.GetString();

        // find the last file separator
        std::string::size_type pos = pathStr.find_last_of(FileSeparator);

        // no file separator file, just return the whole string
        if (pos == std::string::npos)
        {
            return pathStr;
        }

        // create a substring from the beginning
        // of the string to the last file separator
        return pathStr.substr(0, pos);
    }
}