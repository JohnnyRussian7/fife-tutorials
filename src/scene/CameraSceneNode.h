/**********************************************************************
*	Filename: CameraSceneNode.h
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
#ifndef CAMERASCENENODE_H_
#define CAMERASCENENODE_H_

#include "SceneNode.h"
#include "../math/Vector3.h"
#include "../math/Quaternion.h"

class Camera;
class SceneManager;

class CameraSceneNode : public SceneNode
{
public:
	CameraSceneNode(const char* name, SceneManager* manager, 
					const Vector3& position = Vector3(),
					const Quaternion& rotation = Quaternion());
	~CameraSceneNode();

// 	GetViewMatrix();
// 	GetPosition();
// 	GetRotation();
private:
	Camera* m_camera;
};

#endif
