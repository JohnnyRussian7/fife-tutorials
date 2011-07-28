/**********************************************************************
*	Filename: ParticleRenderer.h
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
#ifndef PARTICLERENDERER_H_
#define PARTICLERENDERER_H_

#include "../StdIncludes.h"

#include "../math/Vector3.h"

class Camera;
class ParticleEmitter;

struct ParticleQuad
{
	Vector3 vertex1;
	Vector3 vertex2;
	Vector3 vertex3;
	Vector3 vertex4;
};

class ParticleRenderer
{
public:
	ParticleRenderer();
	~ParticleRenderer();
	void SetEmitter(ParticleEmitter* emitter);
	void SetEnabled(bool enabled);
	bool IsEnabled() const;
	void Update(float time);
	void Render(Camera& camera);

private:
	void SetupBillboard(const Vector3& cameraPosition, const Vector3& particlePosition);

private:
	bool m_enabled;
	ParticleEmitter* m_emitter;
	std::vector<ParticleQuad> m_particleQuads;
};

#endif
