/**********************************************************************
 *	Filename: FpsCameraController.h
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
#ifndef FPSCAMERACONTROLLER_H_
#define FPSCAMERACONTROLLER_H_

#include "../Fife.h"

class FpsCameraController
{
public:
    FpsCameraController(SceneManager* sceneManager, float sensitivity=0.1f, Camera* camera=0);
    ~FpsCameraController();
    
    Camera* GetCamera();
    SceneNode* GetCameraSceneNode();
    
    void yaw(float amount);
    void pitch(float amount);
    void move(const Vector3& translate);
    void update();
private:
    SceneManager* m_sceneManager;
    Camera* m_camera;
    SceneNode* m_cameraNode;
    SceneNode* m_pitchNode;
    bool m_ownsCamera;
    float m_rotationX;
    float m_rotationY;
    float m_sensitivity;
};

#endif

