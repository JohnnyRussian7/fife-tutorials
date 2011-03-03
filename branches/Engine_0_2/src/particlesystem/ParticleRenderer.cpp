/**********************************************************************
*	Filename: ParticleRenderer.cpp
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

#include "ParticleRenderer.h"
#include "ParticleEmitter.h"
#include "Particle.h"
#include "../math/Matrix4.h"
#include "../scene/Camera.h"

ParticleRenderer::ParticleRenderer()
: isEnabled(true)
{
	
}

ParticleRenderer::~ParticleRenderer()
{
	delete m_emitter;
}

void ParticleRenderer::SetEmitter(ParticleEmitter* emitter)
{
	m_emitter = emitter;
}

void ParticleRenderer::SetEnabled(bool enabled)
{
	isEnabled = enabled;
}

bool ParticleRenderer::IsEnabled() const
{
	return isEnabled;
}

void ParticleRenderer::Update(float time)
{
	if (isEnabled && m_emitter)
	{
		m_emitter->Update(time);
		m_emitter->Emit();
	}
}

void ParticleRenderer::Render(Camera& camera)
{
	if (isEnabled && m_emitter)
	{
		const Matrix4& viewMatrix = camera.GetViewMatrix();

		const std::vector<Particle>& particles = m_emitter->GetParticles();

        if (particleQuads.size() != m_emitter->GetNumActiveParticles())
        {
            // preallocate correct number of particle quads
            particleQuads.reserve(m_emitter->GetNumActiveParticles());
        }

		// first setup the quads for the active particles
		for (std::size_t i=0; i < m_emitter->GetNumActiveParticles(); ++i)
		{
			const Particle& particle = particles[i];

			float halfwidth = 0.5f * particle.size;
			float halfheight = 0.5f * particle.size;

			Vector3 horizontal(halfwidth*viewMatrix[0], halfwidth*viewMatrix[1], halfwidth*viewMatrix[2]);
			Vector3 vertical(halfheight*viewMatrix[4], halfheight*viewMatrix[5], halfheight*viewMatrix[6]);
// 			Vector3 horizontal(halfwidth*viewMatrix[0], halfwidth*viewMatrix[4], halfwidth*viewMatrix[8]);
// 			Vector3 vertical(halfheight*viewMatrix[1], halfheight*viewMatrix[5], halfheight*viewMatrix[9]);
 
	 		ParticleQuad quad;
	 		quad.vertex1 = particle.position + horizontal - vertical;
	 		quad.vertex2 = particle.position - horizontal - vertical;
	 		quad.vertex3 = particle.position - horizontal + vertical;
			quad.vertex4 = particle.position + horizontal + vertical;
	 		particleQuads.push_back(quad);
		}

		// get bounding box and calculate edges for drawing
		const AxisAlignedBoundingBox& aabb = m_emitter->GetBoundingBox();
		const Vector3& center = aabb.GetCenter();
		Vector3 diagonal = center - aabb.GetMax();
		Vector3 edges[8];
		edges[0] = Vector3(center.x + diagonal.x, center.y + diagonal.y, center.z + diagonal.z);
		edges[1] = Vector3(center.x + diagonal.x, center.y - diagonal.y, center.z + diagonal.z);
		edges[2] = Vector3(center.x + diagonal.x, center.y - diagonal.y, center.z - diagonal.z);
		edges[3] = Vector3(center.x + diagonal.x, center.y + diagonal.y, center.z - diagonal.z);
		edges[4] = Vector3(center.x - diagonal.x, center.y + diagonal.y, center.z + diagonal.z);
		edges[5] = Vector3(center.x - diagonal.x, center.y - diagonal.y, center.z + diagonal.z);
		edges[6] = Vector3(center.x - diagonal.x, center.y - diagonal.y, center.z - diagonal.z);
		edges[7] = Vector3(center.x - diagonal.x, center.y + diagonal.y, center.z - diagonal.z);
	
		glBegin(GL_LINES);
		glColor3f(1.f, 0.f, 0.f);
		// top of box
		glVertex3f(edges[5].x, edges[5].y, edges[5].z);
		glVertex3f(edges[1].x, edges[1].y, edges[1].z);
		glVertex3f(edges[1].x, edges[1].y, edges[1].z);
		glVertex3f(edges[2].x, edges[2].y, edges[2].z);
		glVertex3f(edges[2].x, edges[2].y, edges[2].z);
		glVertex3f(edges[6].x, edges[6].y, edges[6].z);
		glVertex3f(edges[6].x, edges[6].y, edges[6].z);
		glVertex3f(edges[5].x, edges[5].y, edges[5].z);

		// bottom of box
		glVertex3f(edges[4].x, edges[4].y, edges[4].z);
		glVertex3f(edges[0].x, edges[0].y, edges[0].z);
		glVertex3f(edges[0].x, edges[0].y, edges[0].z);
		glVertex3f(edges[3].x, edges[3].y, edges[3].z);
		glVertex3f(edges[3].x, edges[3].y, edges[3].z);
		glVertex3f(edges[7].x, edges[7].y, edges[7].z);
		glVertex3f(edges[7].x, edges[7].y, edges[7].z);
		glVertex3f(edges[4].x, edges[4].y, edges[4].z);

		// left of box
		glVertex3f(edges[1].x, edges[1].y, edges[1].z);
		glVertex3f(edges[0].x, edges[0].y, edges[0].z);
		glVertex3f(edges[2].x, edges[2].y, edges[2].z);
		glVertex3f(edges[3].x, edges[3].y, edges[3].z);

		// right of box
		glVertex3f(edges[5].x, edges[5].y, edges[5].z);
		glVertex3f(edges[4].x, edges[4].y, edges[4].z);
		glVertex3f(edges[6].x, edges[6].y, edges[6].z);
		glVertex3f(edges[7].x, edges[7].y, edges[7].z);
		glEnd();

        glBegin(GL_QUADS);
        for (std::size_t i=0; i < particleQuads.size(); ++i)
        {
            ParticleQuad& quad = particleQuads[i];

            glColor3f(particles[i].color.r, particles[i].color.g, particles[i].color.b);
 			glTexCoord2f(0.0, 0.0); glVertex3f(quad.vertex1.x, quad.vertex1.y, quad.vertex1.z);
 			glTexCoord2f(1.0, 0.0); glVertex3f(quad.vertex2.x, quad.vertex2.y, quad.vertex2.z);
 			glTexCoord2f(1.0, 1.0); glVertex3f(quad.vertex3.x, quad.vertex3.y, quad.vertex3.z);
 			glTexCoord2f(0.0, 1.0); glVertex3f(quad.vertex4.x, quad.vertex4.y, quad.vertex4.z);
        }
        glEnd();
	}

    particleQuads.clear();
}

void ParticleRenderer::SetupBillboard(const Vector3& camPosition, const Vector3& particlePosition)
{

}