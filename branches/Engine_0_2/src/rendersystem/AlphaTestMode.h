/**********************************************************************
*	Filename: AlphaTestMode.h
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
#ifndef ALPHATESTMODE_H_
#define ALPHATESTMODE_H_

struct AlphaTestType
{
    enum Enum
    {
        Never = 0,
        Less,
        Equal,
        LessEqual,
        Greater,
        NotEqual,
        GreaterEqual,
        Always
    };
};

class AlphaTestMode
{
public:
    //**********************************************************************
    //! @details
    //! constructor
    //!
    //! @note
    //! defaults to disabled
    //**********************************************************************
    AlphaTestMode();

    //**********************************************************************
    //! @details
    //! sets whether alpha test is enabled or not
    //**********************************************************************
    void SetEnabled(bool enabled);

    //**********************************************************************
    //! @details
    //! sets which type of alpha test to perform
    //**********************************************************************
    void SetType(AlphaTestType::Enum alphaTestType);

    //**********************************************************************
    //! @details
    //! sets the value to use for alpha testing
    //**********************************************************************
    void SetValue(float value);

    //**********************************************************************
    //! @details
    //! accessor for whether alpha testing is enabled
    //**********************************************************************
    bool IsEnabled() const;

    //**********************************************************************
    //! @details
    //! accessor for type of alpha test being performed
    //**********************************************************************
    AlphaTestType::Enum GetType() const;

    //**********************************************************************
    //! @details
    //! accessor for the value being used in the alpha test
    //**********************************************************************
    float GetValue() const;

private:
    bool m_enabled;
    AlphaTestType::Enum m_alphaTestType;
    float m_value;
};

bool operator==(const AlphaTestMode& lhs, const AlphaTestMode& rhs);
bool operator!=(const AlphaTestMode& lhs, const AlphaTestMode& rhs);

#endif