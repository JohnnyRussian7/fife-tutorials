
#ifndef SCENE_NODE_H_
#define SCENE_NODE_H_

#include <vector>

class SceneNode
{
public:
	SceneNode(SceneNode* parent);
	~SceneNode();
	
	void AddChild(SceneNode* child);
	void RemoveChild(SceneNode* child);

private:
	SceneNode* m_parent;
	std::vector<SceneNode*> m_childNodes;

};

#endif
