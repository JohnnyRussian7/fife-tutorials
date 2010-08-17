
#ifndef	PARTICLE_RENDERER_H_
#define PARTICLE_RENDERER_H_

#include <vector>

#include "Vector3.h"

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
	bool isEnabled;
	ParticleEmitter* m_emitter;
	std::vector<ParticleQuad> particleQuads;
};

#endif
