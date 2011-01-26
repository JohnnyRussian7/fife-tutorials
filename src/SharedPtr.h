/**********************************************************************
*	Filename: SharedPtr.h
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
#ifndef SHAREDPTR_H_
#define SHAREDPTR_H_

#include "StdIncludes.h"

template <typename T>
class SharedPtr
{
public:
    SharedPtr()
    : m_ptr(0), m_refCount(0)
    {

    }

    template <typename U>
    explicit SharedPtr(U *ptr)
    : m_ptr(ptr), m_refCount(ptr ? new uint32_t(1) : 0)
    {

    }

    SharedPtr(const SharedPtr& rhs)
    : m_ptr(rhs.m_ptr), m_refCount(rhs.m_refCount)
    {
        // increase reference count
        IncRefCount();
    }

    template <typename U>
    SharedPtr(const SharedPtr<U>& rhs)
    {
        m_ptr = rhs.Get();
        m_refCount = rhs.UseCountPtr();
        IncRefCount();
    }

    ~SharedPtr()
    {
        // decrement reference count
        DecRefCount();

        // check to see if we need to delete
        if (m_refCount && m_refCount == 0)
        {
            // delete and set pointers to null
            delete m_ptr;
            delete m_refCount;
            m_ptr = 0;
            m_refCount = 0;
        }
    }

    SharedPtr& operator=(const SharedPtr& rhs)
    {
        // handle self assignment
        if (rhs.m_ptr == m_ptr)
        {
            return *this;
        }

        // store in temporary (which causes a ref count increase
        // and swap with this object
        SharedPtr<T> temp(rhs);
        Swap(temp);
        return *this;
    }

    template <typename U>
    SharedPtr& operator=(const SharedPtr<U>& rhs)
    {
        // handle self assignment
        if (rhs.get() == m_ptr)
        {
            return *this;
        }

        // store in temporary (which causes a ref count increase
        // and swap with this object
        SharedPtr<T> temp(rhs);
        Swap(temp);
        return *this;
    }

    inline T& operator*() const
    {
        assert(m_ptr);
        return *m_ptr;
    }

    inline T* operator->() const
    {
        assert(m_ptr);
        return m_ptr;
    }

    inline T* Get() const
    {
        return m_ptr;
    }

    inline void Reset()
    {
        SharedPtr<T>().Swap(*this);
    }

    inline uint32_t UseCount() const
    {
        assert(m_refCount);
        return *m_refCount;
    }

    inline uint32_t* UseCountPtr() const
    {
        return m_refCount;
    }

    inline bool Unique() const
    {
        assert(m_refCount);
        return (*m_refCount == 1);
    }

    operator bool()
    {
        return (m_ptr != 0);
    }

    bool operator!()
    {
        return (m_ptr == 0);
    }

private:

    inline void Swap(SharedPtr<T>& rhs)
    {
        std::swap(m_ptr, rhs.m_ptr);
        std::swap(m_refCount, rhs.m_refCount);
    }

    inline void IncRefCount()
    {
        if (m_refCount)
        {
            ++(*m_refCount);
        }
    }

    inline void DecRefCount()
    {
        if (m_refCount)
        {
            --(*m_refCount);
        }
    }

private:
    T* m_ptr;
    uint32_t* m_refCount;
};

template <typename T, typename U>
inline bool operator==(const SharedPtr<T>& lhs, const SharedPtr<U>& rhs)
{
    return (lhs.Get() == rhs.Get());
}

template <typename T, typename U>
inline bool operator!=(const SharedPtr<T>& lhs, const SharedPtr<U>& rhs)
{
    return (lhs.Get() != rhs.Get());
}

template<class T, class U> 
inline bool operator<(SharedPtr<T> const& lhs, SharedPtr<U> const& rhs)
{
    return std::less<const void*>()(lhs.Get(), rhs.Get());
}
// convenience function for creating a SharedPtr
template <typename T>
SharedPtr<T> make_shared(T* ptr)
{
    return SharedPtr<T>(ptr);
}

#endif
