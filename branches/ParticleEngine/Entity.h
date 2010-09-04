
#ifndef ENTITY_H_
#define ENTITY_H_

#include <string>

class IMaterial;
class Renderable;

class Entity
{
public:
	Entity(const char* name=0);
	~Entity();

	const char* GetName() const;
    void SetMaterial(IMaterial* material);
    IMaterial* GetMaterial() const;

    virtual Renderable* GetRenderable();
    virtual void Update();

private:
	std::string m_name;
    IMaterial* m_material;
};

#endif