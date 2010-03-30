
#ifndef	PARTICLE_RENDERER_H_
#define PARTICLE_RENDERER_H_

#include <vector>

#include "Vector.h"

class Camera;
class ParticleEmitter;

struct BlendMode
{
	enum Enum
	{
		None = 0,
		Alpha
	};
};

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
	ParticleRenderer(BlendMode::Enum blendMode=BlendMode::Alpha);
	~ParticleRenderer();
	void SetEmitter(ParticleEmitter* emitter);
	void SetEnabled(bool enabled);
	bool IsEnabled() const;
	void SetBlendMode(BlendMode::Enum mode);
	BlendMode::Enum GetBlendMode() const;

	void Update(float time);
	void Render(const Camera& camera);

private:
	void SetupBillboard(const Vector3& cameraPosition, const Vector3& particlePosition);
private:
	bool isEnabled;
	ParticleEmitter* m_emitter;
	BlendMode::Enum blendMode;
	std::vector<ParticleQuad> particleQuads;
};

#endif
