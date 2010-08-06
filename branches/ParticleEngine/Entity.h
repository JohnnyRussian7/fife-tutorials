
#ifndef ENTITY_H_
#define ENTITY_H_

#include <string>

class IMaterial;

class Entity
{
public:
	Entity(const char* name);
	~Entity();

	const char* GetName() const;
    void SetMaterial(IMaterial* material);
    IMaterial* GetMaterial() const;

private:
	std::string m_name;
    IMaterial* m_material;
};

#endif