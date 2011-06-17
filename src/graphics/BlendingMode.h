/**********************************************************************
*	Filename: BlendingMode.h
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
#ifndef BLENDINGMODE_H_
#define BLENDINGMODE_H_

#include "Color.h"

//! enumeration for source blending modes 
struct SrcBlendMode
{
    enum Enum
    {
        Zero = 0,
        One,
        SrcColor,
        OneMinusSrcColor,
        SrcAlpha,
        OneMinusSrcAlpha,
        DestAlpha,
        OneMinusDestAlpha,
        ConstantColor,
        OneMinusConstantColor,
        ConstantAlpha,
        OneMinusConstantAlpha,
        SrcAlphaSaturate
    };
};

//! enumerations for destination blending modes
struct DestBlendMode
{
    enum Enum
    {
        Zero = 0,
        One,
        SrcColor,
        DestColor,
        OneMinusDestColor,
        SrcAlpha,
        OneMinusSrcAlpha,
        DestAlpha,
        OneMinusDestAlpha,
        ConstantColor,
        OneMinusConstantColor,
        ConstantAlpha,
        OneMinusConstantAlpha,
    };
};

class BlendingMode
{
public:
    //!***************************************************************
    //! @details:
    //! constructor
    //!
    //! @note
    //! defaults to blending disabled and constant color of black
    //!***************************************************************
    BlendingMode();

    //!***************************************************************
    //! @details:
    //! sets whether blending is enabled or not
    //!***************************************************************
    void SetEnabled(bool enabled);

    //!***************************************************************
    //! @details:
    //! sets the source blending mode
    //!***************************************************************
    void SetSrcBlendMode(SrcBlendMode::Enum blendMode);

    //!***************************************************************
    //! @details:
    //! sets the destination blending mode
    //!***************************************************************
    void SetDestBlendMode(DestBlendMode::Enum blendMode);

    //!***************************************************************
    //! @details:
    //! sets the blending color to use
    //!
    //! @note 
    //! only applicable for ConstantColor enumeration
    //!***************************************************************
    void SetConstantColor(const Color& color);

    //!***************************************************************
    //! @details:
    //! accessor for the whether blending is enabled
    //!***************************************************************
    bool IsEnabled() const;

    //!***************************************************************
    //! @details:
    //! accessor for the source blending mode
    //!***************************************************************
    SrcBlendMode::Enum GetSrcBlendMode() const;

    //!***************************************************************
    //! @details:
    //! accessor for destination blend mode
    //!***************************************************************
    DestBlendMode::Enum GetDestBlendMode() const;

    //!***************************************************************
    //! @details:
    //! accessor for the blending color
    //!***************************************************************
    Color GetConstantColor() const;

private:
    bool m_enabled;
    SrcBlendMode::Enum m_srcBlendMode;
    DestBlendMode::Enum m_destBlendMode;
    Color m_constantColor;
};

bool operator==(const BlendingMode& lhs, const BlendingMode& rhs);
bool operator!=(const BlendingMode& lhs, const BlendingMode& rhs);

#endif
