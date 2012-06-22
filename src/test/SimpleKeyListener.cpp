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

#include "FpsCameraController.h"

SimpleKeyListener::SimpleKeyListener(Engine* engine, FpsCameraController* fpsCamera) 
: m_engine(engine), m_fpsCamera(fpsCamera), m_name("SimpleKeyListener"), m_translation(Vector3::Zero())
{ 

}

const std::string& SimpleKeyListener::GetName() 
{ 
    return m_name; 
}

void SimpleKeyListener::ResetTranslation()
{
    m_translation = Vector3::Zero();
}

bool SimpleKeyListener::OnKeyPressed(const IKeyEvent& event) 
{
    // make sure to reset the translation values
    // before reading new ones in
    ResetTranslation();
    
    bool translationChange = false;
    const float TranslationAmount = 1.f;
    const float ZoomAmount = 10.f;
    
    if (event.GetKeyCode() == KeyCodes::Left)
    {
        m_translation.x = -TranslationAmount;
        translationChange = true;
    }
    else if (event.GetKeyCode() == KeyCodes::Right)
    {
        m_translation.x = TranslationAmount;
        translationChange = true;
    }
    else if (event.GetKeyCode() == KeyCodes::Up)
    {
        m_translation.y = TranslationAmount;
        translationChange = true;
    }
    else if (event.GetKeyCode() == KeyCodes::Down)
    {
        m_translation.y = -TranslationAmount;
        translationChange = true;
    }
    else if (event.GetKeyCode() == KeyCodes::Plus)
    {
        const float ZoomAmount = 10;
        
        m_translation.z = -ZoomAmount;
        m_fpsCamera->move(m_translation);
    }
    else if (event.GetKeyCode() == KeyCodes::Minus)
    {
        m_translation.z = ZoomAmount;
        m_fpsCamera->move(m_translation);
    }

    if (translationChange)
    {
        m_fpsCamera->move(m_translation);
    }

    return true;
}

bool SimpleKeyListener::OnKeyReleased(const IKeyEvent& event) 
{
    if (event.GetKeyCode() == KeyCodes::Escape)
    {
        m_engine->Quit();
    }
    else if (event.GetKeyCode() == KeyCodes::KeyC)
    {
        // toggle cull mode
        if (m_cullMode.GetCullType() != CullType::Front)
        {
            m_cullMode.SetCullType(CullType::Front);
            std::cout << "Front face culling enabled" << std::endl;
        }
        else
        {
            m_cullMode.SetCullType(CullType::Back);
            std::cout << "Back face culling enabled" << std::endl;
        }
        
        m_cullMode.SetEnabled(true);
        m_engine->GetSceneManager()->GetRootSceneNode()->SetCullMode(m_cullMode);
    }
    else if (event.GetKeyCode() == KeyCodes::KeyF)
    {
        // toggle between wireframe and fill
        if (m_fillMode.GetFillType() != FillType::Fill)
        {
            m_fillMode.SetFillType(FillType::Fill);
            std::cout << "Fill mode enabled" << std::endl;
        }
        else
        {
            m_fillMode.SetFillType(FillType::Line);
            std::cout << "Wireframe mode enabled" << std::endl;
            
        }
        
        m_engine->GetSceneManager()->GetRootSceneNode()->SetFillMode(m_fillMode);
    }
    else if (event.GetKeyCode() == KeyCodes::KeyP)
    {
        // toggle between CCW and CW winding
        if (m_windingMode.GetWindingType() == WindingType::CounterClockwise)
        {
            m_windingMode.SetWindingType(WindingType::Clockwise);
            std::cout << "Clockwise winding enabled" << std::endl;
        }
        else
        {
            m_windingMode.SetWindingType(WindingType::CounterClockwise);
            std::cout << "Counter clockwise winding enabled" << std::endl;
        }
        
        m_engine->GetSceneManager()->GetRootSceneNode()->SetPolygonWindingMode(m_windingMode);
    }

    return true;
}