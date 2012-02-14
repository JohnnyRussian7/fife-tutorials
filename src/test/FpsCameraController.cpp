/**********************************************************************
 *	Filename: FpsCameraController.cpp
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
#include "PrecompiledIncludes.h"

#include "FpsCameraController.h"

FpsCameraController::FpsCameraController(SceneManager* sceneManager, Camera* camera)
: m_sceneManager(sceneManager), m_ownsCamera(false), m_rotationX(0.f), m_rotationY(0.f)
{
    if (camera)
    {
        m_camera = camera;
    }
    else
    {
        m_camera = m_sceneManager->CreateCamera("FpsCamera");
        m_ownsCamera = true;
    }
    
    m_cameraNode = m_sceneManager->CreateSceneNode("CameraNode");
    m_sceneManager->GetRootSceneNode()->AddChild(m_cameraNode);
    m_cameraNode->SetPosition(0, 0, 50);
    m_camera->LookAt(0, 0, 0);
    m_pitchNode = m_sceneManager->CreateSceneNode("PitchNode");
    m_cameraNode->AddChild(m_pitchNode);
    m_pitchNode->AddEntity(m_camera);
    m_sceneManager->AddCamera(m_camera);
}

FpsCameraController::~FpsCameraController()
{
    if (m_ownsCamera)
    {
        m_sceneManager->DestroyCamera(m_camera);
        m_camera = 0;
    }
    
    m_sceneManager->DestroySceneNode(m_pitchNode);
    m_sceneManager->DestroySceneNode(m_cameraNode);
}

Camera* FpsCameraController::GetCamera()
{
    return m_camera;
}

SceneNode* FpsCameraController::GetCameraSceneNode()
{
    return m_cameraNode;
}

void FpsCameraController::yaw(float amount)
{
    m_rotationX = DegToRad(amount);
    m_cameraNode->Yaw(m_rotationX);
}

void FpsCameraController::pitch(float amount)
{
    m_rotationY = DegToRad(amount);
    m_pitchNode->Pitch(m_rotationY);
}

void FpsCameraController::move(const Vector3& translate)
{
    //m_cameraNode->SetPosition(m_cameraNode->GetPosition() + translate);
    
    if (translate.y != 0.f)
    {
        m_cameraNode->SetPosition(Vector3(0.f, translate.y, 0.f));
    }
    
    Vector3 xzTranslate(translate.x, 0.f, translate.z);
    
    m_cameraNode->Translate(m_cameraNode->GetOrientation() * m_pitchNode->GetOrientation()  * xzTranslate);
}

void FpsCameraController::update()
{
    //Quaternion pitch = FromAxisAngle(Vector3::UnitX(), m_rotationY);
    //Quaternion yaw = FromAxisAngle(Vector3::UnitY(), m_rotationX);
    
    //m_cameraNode->SetOrientation(yaw * pitch);
}

