/**********************************************************************
*	Filename: ImageManager.cpp
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

#include "ImageManager.h"
#include "IImageLoader.h"
#include "IImage.h"
#include "../filesystem/IPath.h"
#include "../filesystem/Path.h"

namespace graphics
{
    ImageManager::ImageManager()
    {
        m_loaders.push_back(make_shared(graphics::CreateImageLoader("png")));
    }

    ImagePtr ImageManager::CreateImage(const std::string& file, const char* name, IImageLoader* loader)
    {
        return CreateImage(filesystem::Path(file), name, loader);
    }

    ImagePtr ImageManager::CreateImage(const filesystem::IPath& path, const char* name, IImageLoader* loader)
    {
        if (name)
        {
            ImageContainer::iterator iter = m_images.find(std::string(name));

            if (iter != m_images.end())
            {
                // image already exists so lets just return it here
                return iter->second;
            }
        }

        // attempt to create our own loader if one was not provided
        if (!loader)
        {
            // TODO - this will need to be expanded to support 
            //        more image formats
            ImageLoaderPtr loaderPtr = GetImageLoader(path);

            if (loaderPtr)
            {
                loader = loaderPtr.Get();
            }
        }

        if (loader)
        {
            // load the image
            IImage* image = loader->Load(path, name);

            // create a shared pointer from the loaded image
            if (image)
            {
                ImagePtr ptr = make_shared(image);  

                std::pair<ImageContainer::iterator, bool> retVal = m_images.insert(std::make_pair(ptr->GetName(), ptr));
                return retVal.first->second;
            }
        }

        return ImagePtr();
    }

    bool ImageManager::AddImage(IImage* image)
    {
        if (image)
        {
            ImagePtr sharedImage(image);
            std::pair<ImageContainer::iterator, bool> retVal = m_images.insert(std::make_pair(sharedImage->GetName(), sharedImage));

            return retVal.second;
        }

        return false;   
    }

    void ImageManager::RemoveImage(IImage* image)
    {
        // TODO - may need a faster way to do this if it becomes
        //        a performance bottleneck, for now just loop
        ImageContainer::iterator iter = m_images.begin();
        for (; iter != m_images.end(); ++iter)
        {
            if (iter->second.Get() == image)
            {
                m_images.erase(iter);
                break;
            }
        }
    }

    void ImageManager::RemoveImage(const char* name)
    {
        if (name)
        {
            ImageContainer::iterator iter = m_images.find(name);
            if (iter != m_images.end())
            {
                m_images.erase(iter);
            }
        }
    }

    void ImageManager::RemoveAllImages()
    {
        m_images.clear();
    }

    void ImageManager::RemoveUnusedImages()
    {
        ImageContainer::iterator iter = m_images.begin();
        for (; iter != m_images.end(); ++iter)
        {
            if (iter->second.Unique())
            {
                m_images.erase(iter);
            }
        }
    }

    ImageManager::ImageLoaderPtr ImageManager::GetImageLoader(const filesystem::IPath& path) const
    {
        ImageLoaderContainer::const_iterator iter;
        for (iter = m_loaders.begin(); iter != m_loaders.end(); ++iter)
        {
            if ((*iter)->IsLoadable(path))
            {
                return *iter;
            }
        }

        return ImageLoaderPtr();
    }
}
