
#include "ParticleRenderer.h"
#include "ParticleEmitter.h"
#include "Particle.h"
#include "Camera.h"
#include "Matrix.h"

#ifdef WIN32
#include <windows.h>
#include <gl/glu.h>
#include <gl/gl.h>
#else
#include <gl/gl.h>
#endif

ParticleRenderer::ParticleRenderer(BlendMode::Enum blendMode)
: isEnabled(true), blendMode(blendMode)
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

void ParticleRenderer::SetBlendMode(BlendMode::Enum mode)
{
	blendMode = mode;
}

BlendMode::Enum ParticleRenderer::GetBlendMode() const
{
	return blendMode;
}

void ParticleRenderer::Update(float time)
{
	if (isEnabled && m_emitter)
	{
		m_emitter->Update(time);
		m_emitter->Emit();
	}
}

void ParticleRenderer::Render(const Camera& camera)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
	glTranslatef(0.f, 0.f, -80.f);

	if (isEnabled && m_emitter)
	{
		Matrix4 viewMatrix = camera.GetViewMatrix();

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

			float halfwidth = 0.5 * particle.size;
			float halfheight = 0.5 * particle.size;

			Vector3 horizontal(halfwidth*viewMatrix.matrix[0], halfwidth*viewMatrix.matrix[4], halfwidth*viewMatrix.matrix[8]);
			Vector3 vertical(halfheight*viewMatrix.matrix[1], halfheight*viewMatrix.matrix[5], halfheight*viewMatrix.matrix[9]);

			
	 		//Vector3 position = rotation * particle.position;
	 
	 		ParticleQuad quad;
	 		quad.vertex1 = /*position*/ particle.position + horizontal - vertical /*+ Vector3(particle.size, -particle.size, 0)*/;
	 		quad.vertex2 = /*position*/ particle.position - horizontal - vertical /*+ Vector3(particle.size, -particle.size, 0)*/;
	 		quad.vertex3 = /*position*/ particle.position - horizontal + vertical /*+ Vector3(particle.size, particle.size, 0)*/;
			quad.vertex4 = /*position*/ particle.position + horizontal + vertical /*+ Vector3(-particle.size, particle.size, 0)*/;
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