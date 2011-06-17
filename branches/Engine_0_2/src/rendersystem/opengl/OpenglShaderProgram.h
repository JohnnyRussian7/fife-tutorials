/**********************************************************************
*	Filename: OpenglShaderProgram.h
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
#ifndef OPENGLSHADERPROGRAM_H_
#define OPENGLSHADERPROGRAM_H_

#include "../IShaderProgram.h"

class IShader;

namespace opengl {

    class OpenglShaderProgram : public IShaderProgram
    {
    public:
        OpenglShaderProgram(IShader* vertexShader, IShader* fragmentShader);

        ~OpenglShaderProgram();

        virtual IShader* GetVertexShader() const;
        virtual void SetVertexShader(IShader* shader);

        virtual IShader* GetFragmentShader() const;
        virtual void SetFragmentShader(IShader* shader);

        virtual void Enable();
        virtual void Disable();

        bool IsLinked() const;

        void operator()();

    private:
        void Init();
        void Destroy();

    private:
        uint32_t m_id;
        IShader* m_vertexShader;
        IShader* m_fragmentShader;
        bool m_linked;
    };
}

#endif
