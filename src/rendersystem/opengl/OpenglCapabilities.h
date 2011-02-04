/**********************************************************************
*	Filename: OpenglCapabilities.h
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
#ifndef OPENGLCAPABILITIES_H_
#define OPENGLCAPABILITIES_H_

struct OpenglVersion
{
    enum Enum
    {
        Unknown = 0,
        _1_2,
        _1_3,
        _1_4,
        _1_5,
        _2_0,
        _2_1,
        _3_0
    };

    static std::string ToString(Enum version);
};

struct GlslVersion
{
    enum Enum
    {
        Unknown = 0,
        _1_0,
        _1_1,
        _1_2,
        _1_3
    };
};

class OpenglCapabilities
{
public:

    // singleton access
    static OpenglCapabilities* Instance();

    OpenglVersion::Enum GetOpenglVersion() const;
    GlslVersion::Enum GetGlslVersion() const;
    bool HasVboSupport() const;
    bool HasNonPow2TextureSupport() const;
    bool HasShaderSupport() const;

private:
    OpenglCapabilities();
    OpenglCapabilities(const OpenglCapabilities&);
    OpenglCapabilities& operator=(const OpenglCapabilities&);
};

#endif
