/**********************************************************************
*	Filename: IComponent.h
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
#ifndef ICOMPONENT_H_
#define ICOMPONENT_H_

class IEntity;

class IComponent
{
public:
    virtual ~IComponent() { };

    virtual std::string GetName() = 0;
    virtual void SetOwner(IEntity* entity) = 0;
    virtual void Update(uint32_t time) = 0;
};

#endif
