/**********************************************************************
 *	Filename: SimpleApplication.h
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
#ifndef SIMPLEAPPLICATION_H_
#define SIMPLEAPPLICATION_H_

#include "../Fife.h"

class FpsCameraController;
class SimpleKeyListener;
class SimpleMouseListener;

class SimpleApplication
{
public:
    SimpleApplication();
    ~SimpleApplication();
    
    void Run();
    void Stop();
private:
    void CreateEngine();
    void CreateCamera();
    void CreateMouseListener();
    void CreateKeyListener();
private:
    Engine* m_engine;
    FpsCameraController* m_fpsCamera;
    SimpleKeyListener* m_keyListener;
    SimpleMouseListener* m_mouseListener;
};

#endif
