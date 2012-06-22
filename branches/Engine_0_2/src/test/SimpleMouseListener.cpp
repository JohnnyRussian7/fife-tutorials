/**********************************************************************
*	Filename: SimpleMouseListener.cpp
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

#include "SimpleMouseListener.h"

#include "FpsCameraController.h"

SimpleMouseListener::SimpleMouseListener(FpsCameraController* fpsCamera) 
: m_name("SimpleMouseListener"), m_fpsCamera(fpsCamera), m_initialized(false)
{ 

}

const std::string& SimpleMouseListener::GetName() 
{ 
    return m_name; 
}

bool SimpleMouseListener::OnMouseMoved(const IMouseEvent& event) 
{
    //float yawAmount = (event.GetXPos() - m_lastX) * 0.015;
    //float pitchAmount = (event.GetYPos() - m_lastY) * 0.015;
    float yaw = -event.GetRelativeX();
    float pitch = -event.GetRelativeY();
    
	//std::cout << "yaw: " << yaw << std::endl;
	//std::cout << "pitch: " << pitch << std::endl;
	
    if  (m_initialized)
    {
        //m_cam->Rotate(test);
        //m_cam->Yaw(yawAmount);
        //m_cam->Pitch(pitchAmount);
        m_fpsCamera->yaw(yaw);
        m_fpsCamera->pitch(pitch);
        //std::cout << "yaw: " << yaw << "\t\t" << "pitch:" << pitch << std::endl;
    }
    
    m_initialized = true;

    return true;
}

bool SimpleMouseListener::OnMousePressed(const IMouseEvent& event) 
{     
    return true; 
}

bool SimpleMouseListener::OnMouseReleased(const IMouseEvent& event) 
{ 
    return true; 
}

bool SimpleMouseListener::OnMouseWheel(const IMouseEvent& event) 
{
    static float ZoomAmount = 10;

    //m_cam->Translate(Vector3(0.f, 0.f, -ZoomAmount*event.GetWheelDelta()));

    return true;
}

bool SimpleMouseListener::OnMouseDragged(const IMouseEvent& event)
{
    float xRel = event.GetRelativeX();
    float yRel = event.GetRelativeY();

	SceneNode* root = m_fpsCamera->GetSceneManager()->GetRootSceneNode();
	
    if (event.IsButtonPressed(MouseButtons::RightButton))
    {
		root->Translate(xRel, yRel, 0);
        //root->Yaw(yaw);
        //root->Pitch(pitch);
    }
	else if (event.IsButtonPressed(MouseButtons::LeftButton))
	{
		root->Yaw(DegToRad(xRel));
		root->Pitch(DegToRad(yRel));
	}
	
	return true;
}