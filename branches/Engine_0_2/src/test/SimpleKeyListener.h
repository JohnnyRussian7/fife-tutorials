/**********************************************************************
*	Filename: SimpleKeyListener.h
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
#ifndef SIMPLEKEYLISTENER_H_
#define SIMPLEKEYLISTENER_H_

#include "../Fife.h"

#include "FpsCameraController.h"

class SimpleKeyListener : public IKeyListener
{
public:
    SimpleKeyListener(Engine& engine, const FpsCameraController& fpsCamera);

    virtual const std::string& GetName();
    virtual bool OnKeyPressed(const IKeyEvent& event);
    virtual bool OnKeyReleased(const IKeyEvent& event);

private:
    Engine& m_engine;
    FpsCameraController m_fpsCamera;
    std::string m_name;
    float m_xTrans;
    float m_yTrans;
    float m_zTrans;
    FillMode m_fillMode;
    CullMode m_cullMode;
};

#endif