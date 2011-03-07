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

        //!***************************************************************
        //! @details:
        //! returns the full path in the native OS format
        //!
        //! @return: 
        //! std::string
        //! 
        //!***************************************************************
        virtual std::string GetString() const = 0;

        //!***************************************************************
        //! @details:
        //! returns the full path up to the last file separator character
        //! in the native OS format
        //!
        //! @return: 
        //! std::string
        //! 
        //!***************************************************************
        virtual std::string GetParentPath() const = 0;

        //!***************************************************************
        //! @details:
        //! returns a string from the last file separator character to
        //! the end of the path string in the native OS format
        //!
        //! @note: 
        //! this will included the extension if one exists
        //!
        //! @return: 
        //! std::string
        //! 
        //!***************************************************************
        virtual std::string GetFilename() const = 0;

        //!***************************************************************
        //! @details:
        //! returns the extensions including the '.' character 
        //! in the native OS format
        //!
        //! @note
        //! will return an empty string if no extension present
        //!
        //! @return: 
        //! std::string
        //! 
        //!***************************************************************
        virtual std::string GetExtension() const = 0;

        //!***************************************************************
        //! @details:
        //! checks to see if an extension is present on the path string
        //!
        //! @return: 
        //! bool
        //! 
        //!***************************************************************
        virtual bool HasExtension() const = 0;

        //!***************************************************************
        //! @details:
        //! replaces the current extension with the one provided in the
        //! input argument
        //!
        //! @param[in]: extension
        //! the new extension
        //!
        //! @return: 
        //! void
        //! 
        //!***************************************************************
        virtual void ReplaceExtension(const std::string& extension) = 0;

        //!***************************************************************
        //! @details:
        //! appends a string onto the end of the current path
        //!
        //! @note:
        //! automatically appends a file separator between the current
        //! path and the one to be appended
        //!
        //! @param[in]: path
        //! the path string to be appended
        //!
        //! @return: 
        //! void
        //! 
        //!***************************************************************
        virtual void Append(const std::string& path) = 0;

        //!***************************************************************
        //! @details:
        //! appends a path object onto the end of the current path
        //!
        //! @note:
        //! automatically appends a file separator between the current
        //! path and the one to be appended
        //!
        //! @param[in]: path
        //! the path object to be appended
        //!
        //! @return: 
        //! void
        //! 
        //!***************************************************************
        virtual void Append(const IPath& path) = 0;

        //!***************************************************************
        //! @details:
        //! overloaded the '/=' operator to allow convenient appending
        //! of path strings
        //!
        //! @note:
        //! automatically appends a file separator between the current
        //! path and the one to be appended
        //!
        //! @param[in]: path
        //! the path string to append
        //!
        //! @return: 
        //! IPath&
        //! 
        //!***************************************************************
        virtual IPath& operator/=(const std::string& path) = 0;

        //!***************************************************************
        //! @details:
        //! overloaded the '/=' operator to allow convenient appending
        //! of path objects
        //!
        //! @note:
        //! automatically appends a file separator between the current
        //! path and the one to be appended
        //!
        //! @param[in]: path
        //! the path object to append
        //!
        //! @return: 
        //! IPath&
        //! 
        //!***************************************************************
        virtual IPath& operator/=(const IPath& path) = 0;
    };
}

#endif
