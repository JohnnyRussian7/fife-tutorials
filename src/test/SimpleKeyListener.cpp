/**********************************************************************
*	Filename: SimpleKeyListener.cpp
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

#include "SimpleKeyListener.h"

SimpleKeyListener::SimpleKeyListener(Engine& engine, Camera* cam) 
: m_engine(engine), m_cam(cam), m_name("SimpleKeyListener"), m_xTrans(0.f), m_yTrans(0.f), m_zTrans(0.f)
{ 

}

const std::string& SimpleKeyListener::GetName() 
{ 
    return m_name; 
}

float gYaw = 0;
float gPitch = 0;
bool SimpleKeyListener::OnKeyPressed(const IKeyEvent& event) 
{ 
    bool translationChange = false;
    const float TranslationAmount = 1.f;

    if (event.GetKeyCode() == KeyCodes::KeyR)
    {
        if (gYaw > 360)
        {
            gYaw = 0;
        }
        else
        {
            gYaw += 1;
        }
        
        if (gPitch > 90)
        {
            gPitch = 0;
        }
        else
        {
            gPitch += 1;
        }
        
        m_cam->Yaw(gYaw);
        m_cam->Pitch(gPitch);
    }
    
    if (event.GetKeyCode() == KeyCodes::Left)
    {
        m_xTrans -= TranslationAmount;
        translationChange = true;
    }
    else if (event.GetKeyCode() == KeyCodes::Right)
    {
        m_xTrans += TranslationAmount;
        translationChange = true;
    }
    else if (event.GetKeyCode() == KeyCodes::Up)
    {
        m_zTrans -= TranslationAmount;
        translationChange = true;
    }
    else if (event.GetKeyCode() == KeyCodes::Down)
    {
        m_zTrans += TranslationAmount;
        translationChange = true;
    }
    else if (event.GetKeyCode() == KeyCodes::Plus)
    {
        const float ZoomAmount = 10;
        
        m_cam->Translate(Vector3(0.f, 0.f, -ZoomAmount));
    }
    else if (event.GetKeyCode() == KeyCodes::Minus)
    {
        const float ZoomAmount = 10;
        
        m_cam->Translate(Vector3(0.f, 0.f, ZoomAmount));
    }

    if (translationChange)
    {
        m_cam->Translate(m_xTrans, m_yTrans, m_zTrans);
    }

    return true;
}

bool SimpleKeyListener::OnKeyReleased(const IKeyEvent& event) 
{
    if (event.GetKeyCode() == KeyCodes::Escape)
    {
        m_engine.Quit();
    }
    else if (event.GetKeyCode() == KeyCodes::KeyC)
    {
        // toggle cull mode
        if (m_cullMode.GetCullType() != CullType::Front)
        {
            m_cullMode.SetCullType(CullType::Front);
        }
        else
        {
            m_cullMode.SetCullType(CullType::Back);
        }
        
        m_cullMode.SetEnabled(true);
        m_engine.GetSceneManager()->GetRootSceneNode()->SetCullMode(m_cullMode);
    }
    else if (event.GetKeyCode() == KeyCodes::KeyP)
    {
        // toggle between wireframe and fill
        if (m_fillMode.GetFillType() != FillType::Fill)
        {
            m_fillMode.SetFillType(FillType::Fill);
            m_engine.GetSceneManager()->GetRootSceneNode()->SetFillMode(m_fillMode);
        }
        else
        {
            m_fillMode.SetFillType(FillType::Line);
            m_engine.GetSceneManager()->GetRootSceneNode()->SetFillMode(m_fillMode);
        }
    }

    return true;
}