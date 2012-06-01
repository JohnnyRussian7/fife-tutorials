/**********************************************************************
*	Filename: SimpleMouseListener.h
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
#ifndef SIMPLEMOUSELISTENER_H_
#define SIMPLEMOUSELISTENER_H_

#include "../Fife.h"

class FpsCameraController;

class SimpleMouseListener : public IMouseListener
{
public:
    SimpleMouseListener(FpsCameraController* fpsCamera);

    virtual const std::string& GetName();
    virtual bool OnMouseMoved(const IMouseEvent& event);
    virtual bool OnMousePressed(const IMouseEvent& event);
    virtual bool OnMouseReleased(const IMouseEvent& event);
    virtual bool OnMouseWheel(const IMouseEvent& event);
    virtual bool OnMouseDragged(const IMouseEvent& event);

private:
    FpsCameraController* m_fpsCamera;
    float m_yawAngle;
    std::string m_name;
    bool m_initialized;
};

#endif