/**********************************************************************
*	Filename: SceneNode.cpp
*	
*	Copyright (C) 2010, FIFE team
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

#include "SceneNode.h"
#include "SceneManager.h"
#include "../IEntity.h"
#include "../RenderComponent.h"
#include "../math/MathUtil.h"
#include "../rendersystem/RenderOperation.h"
#include "../utility/CheckedCast.h"
#include "Camera.h"

namespace
{
	std::string CreateUniqueSceneNodeName()
	{
		// automated counting for name generation, in case the user doesn't provide a name
		static uint32_t uniqueNumber = 0;
        static std::string baseName = "SceneNode";

		std::ostringstream oss;
		oss << baseName << "_" << uniqueNumber;
		
		const std::string name = oss.str();
		++uniqueNumber;

		return name;
	}
}

SceneNode::SceneNode(const char* name, SceneManager* manager)
: m_name(""), m_sceneManager(manager), m_parent(0), m_scale(1, 1, 1), m_position(Vector3::Zero()),
m_orientation(Quaternion::Identity()), m_relativeScale(1, 1, 1), m_relativePosition(Vector3::Zero()),
m_relativeOrientation(Quaternion::Identity()), m_requiresUpdate(false), m_updateTransform(false),
m_localBlendingMode(false), m_localCullMode(false), m_localFillMode(false)
{
	if (name)
	{
		m_name = std::string(name);
	}
	else
	{
		m_name = CreateUniqueSceneNodeName();
	}

    m_transformComponent = new TransformComponent();
    MarkDirty();
}

SceneNode::~SceneNode()
{
	RemoveAllChildren();
    delete m_transformComponent;
    m_transformComponent = 0;
}

const char* SceneNode::GetName() const
{
	return m_name.c_str();
}

void SceneNode::SetParent(SceneNode* parent)
{
    if (!parent)
    {
        // TODO - invalid parameter do nothing, may need to report this error
        return;
    }

	if (m_parent != 0)
	{
		// remove ourselves from our current parent
        // if we have one, but tell parent not to 
        // delete us
		m_parent->RemoveChild(this, false);
        m_parent->GetTransformComponent()->RemoveTransformChangedListener(GetTransformComponent());
	}

    // set new parent and add ourselves as a listener for transform changes
	m_parent = parent;
    m_parent->GetTransformComponent()->AddTransformChangedListener(GetTransformComponent());
    GetTransformComponent()->SetParent(m_parent->GetTransformComponent());

    MarkDirty();
}

void SceneNode::SetParent(const char* parentName)
{
    SceneNode* parent = m_sceneManager->GetSceneNode(parentName);
	SetParent(parent);
}

SceneNode* SceneNode::GetParent() const
{
	return m_parent;
}

void SceneNode::AddChild(SceneNode* child)
{
	if (child)
	{
        child->SetParent(this);
		m_childNodes.push_back(child);
	}
}

void SceneNode::RemoveChild(SceneNode* child, bool shouldDeleteChild)
{
	if (child)
	{
		std::vector<SceneNode*>::iterator iter = m_childNodes.begin();
		for (; iter != m_childNodes.end(); ++iter)
		{
			if (*iter == child)
			{
				if (shouldDeleteChild)
				{
					m_sceneManager->DestroySceneNode(child);
				}
				m_childNodes.erase(iter);
				break;
			}
		}
	}
}

void SceneNode::RemoveAllChildren()
{
	// delete all children
	std::vector<SceneNode*>::iterator iter = m_childNodes.begin();
	for (; iter != m_childNodes.end(); ++iter)
	{
		m_sceneManager->DestroySceneNode(*iter);
	}
	m_childNodes.clear();
}

void SceneNode::AddEntity(IEntity* entity)
{
    if (entity)
    {
        entity->SetParent(this);
        TransformComponent* transformComponent = checked_cast<TransformComponent*>(entity->GetComponent("Transform"));
        transformComponent->SetParent(m_transformComponent);
        m_entities.push_back(entity);
    }
}

void SceneNode::RemoveEntity(IEntity* entity, bool shouldDeleteEntity)
{
    if (entity)
    {
        for (EntityContainer::iterator iter = m_entities.begin(); iter != m_entities.end(); ++iter)
        {
            if (*iter == entity)
            {
                if (shouldDeleteEntity)
                {
                    delete *iter;
                }
                m_entities.erase(iter);
                break;
            }
        }
    }
}

void SceneNode::RemoveEntity(const char* name, bool shouldDeleteEntity)
{
    if (name)
    {
        for (EntityContainer::iterator iter = m_entities.begin(); iter != m_entities.end(); ++iter)
        {
            if ((*iter)->GetName() == name)
            {
                TransformComponent* transformComponent = checked_cast<TransformComponent*>((*iter)->GetComponent("Transform"));
                transformComponent->SetParent(0);
                if (shouldDeleteEntity)
                {
                    delete *iter;
                }
                m_entities.erase(iter);
                break;
            }
        }
    }
}

void SceneNode::RemoveAllEntities()
{
    for (EntityContainer::iterator iter = m_entities.begin(); iter != m_entities.end(); ++iter)
    {
        TransformComponent* transformComponent = checked_cast<TransformComponent*>((*iter)->GetComponent("Transform"));
        transformComponent->SetParent(0);
        delete *iter;
    }
    m_entities.clear();
}

TransformComponent* SceneNode::GetTransformComponent() const
{
    return m_transformComponent;
}

void SceneNode::GetRenderOperations(std::vector<RenderOperation>& renderOperations)
{
    // cache the current blend mode to add to each render operation
    const BlendingMode& blendingMode = GetBlendingMode();

    // cache current cull mode to add to each render operation
    const CullMode& cullMode = GetCullMode();

    // cache current winding mode to add to each render operation
    const PolygonWindingMode& windingMode = GetPolygonWindingMode();

    // cache current fill mode to add to each render operation
    const FillMode& fillMode = GetFillMode();

    // cache current alpha test mode to add to each render operation
    const AlphaTestMode& alphaTestMode = GetAlphaTestMode();

    // add all of this scene nodes renderables
    EntityContainer::iterator entityIter;
    for (entityIter = m_entities.begin(); entityIter != m_entities.end(); ++entityIter)
    {
        RenderComponent* renderComponent = checked_cast<RenderComponent*>((*entityIter)->GetComponent("Render"));
        if (renderComponent)
        {
            Matrix4 transform = renderComponent->GetTransform();
            if (m_name != "CameraNode" || m_name != "PitchNode")
            {
                //transform.SetX(Vector3(1, 0, 0));
                //transform.SetY(-m_sceneManager->GetCamera()->GetViewMatrix().GetY());
                //transform.SetZ(-m_sceneManager->GetCamera()->GetViewMatrix().GetZ());
            }
            
            RenderOperation operation;
            operation.SetTransform(transform);
            operation.SetPrimitiveType(renderComponent->GetPrimitiveType());
            operation.SetVertexBuffer(renderComponent->GetVertexBuffer());
            operation.SetIndexBuffer(renderComponent->GetIndexBuffer());
            operation.SetMaterial(renderComponent->GetMaterial());
            operation.SetBlendingMode(blendingMode);
            operation.SetCullMode(cullMode);
            operation.SetPolygonWindingMode(windingMode);
            operation.SetFillMode(fillMode);
            operation.SetAlphaTestMode(alphaTestMode);
            renderOperations.push_back(operation);
        }
    }

    // now for each child scene node allow them to add their renderables
    std::vector<SceneNode*>::iterator sceneNodeIter;
    for (sceneNodeIter = m_childNodes.begin(); sceneNodeIter != m_childNodes.end(); ++sceneNodeIter)
    {
        (*sceneNodeIter)->GetRenderOperations(renderOperations);
    }
}

const Vector3& SceneNode::GetScale() const
{
   return m_transformComponent->GetScale();
}

const Vector3& SceneNode::GetPosition() const
{
    return m_transformComponent->GetPosition();
}

const Quaternion& SceneNode::GetOrientation() const
{
	return m_transformComponent->GetOrientation();
}

const Vector3& SceneNode::GetRelativeScale() const
{
	return m_transformComponent->GetRelativeScale();
}

const Vector3& SceneNode::GetRelativePosition() const
{
	return m_transformComponent->GetRelativePosition();
}

const Quaternion& SceneNode::GetRelativeOrientation() const
{
	return m_transformComponent->GetRelativeOrientation();
}

void SceneNode::SetScale(const Vector3& scale)
{
	m_transformComponent->SetScale(scale);
}

void SceneNode::SetScale(float x, float y, float z)
{
	SetScale(Vector3(x,y,z));
}

void SceneNode::SetPosition(const Vector3& position)
{
	m_transformComponent->SetPosition(position);
}

void SceneNode::SetPosition(float x, float y, float z)
{
	SetPosition(Vector3(x,y,z));
}

void SceneNode::SetOrientation(const Quaternion& orientation)
{
	m_transformComponent->SetOrientation(orientation);
}

void SceneNode::SetOrientation(const Vector3& axis, float angle)
{
	SetOrientation(FromAxisAngle(axis, angle));
}

void SceneNode::SetBlendingMode(const BlendingMode& blendingMode)
{
    // save blending mode locally
    m_blendingMode = blendingMode;
    m_localBlendingMode = true;
}

const BlendingMode& SceneNode::GetBlendingMode()
{
    // attempt to perform a lazy update, if the parent's blending mode has changed
    // if the blending mode is not the same as our parent and we haven't set it
    // directly, then update it from the parent
    if (m_parent && m_blendingMode != m_parent->GetBlendingMode() && !m_localBlendingMode)
    {
        m_blendingMode = m_parent->GetBlendingMode();
    }

    return m_blendingMode;
}

void SceneNode::SetCullMode(const CullMode& cullMode)
{
    // save cull mode locally
    m_cullMode = cullMode;
    m_localCullMode = true;
}

const CullMode& SceneNode::GetCullMode()
{
    // attempt to perform a lazy update, if the parent's cull mode has changed
    // if the cull mode is not the same as our parent and we haven't set it
    // directly, then update it from the parent
    if (m_parent && m_cullMode != m_parent->GetCullMode() && !m_localCullMode)
    {
        m_cullMode = m_parent->GetCullMode();
    }

    return m_cullMode;
}

void SceneNode::SetPolygonWindingMode(const PolygonWindingMode& windingMode)
{
    // save winding mode locally
    m_windingMode = windingMode;
    m_localWindingMode = true;
}

const PolygonWindingMode& SceneNode::GetPolygonWindingMode()
{
    // attempt to perform a lazy update, if the parent's winding mode has changed
    // if the winding mode is not the same as our parent and we haven't set it
    // directly, then update it from the parent
    if (m_parent && m_windingMode != m_parent->GetPolygonWindingMode() && !m_localWindingMode)
    {
        m_windingMode = m_parent->GetPolygonWindingMode();
    }

    return m_windingMode;
}

void SceneNode::SetFillMode(const FillMode& fillMode)
{
    // save fill mode locally
    m_fillMode = fillMode;
    m_localFillMode = true;
}

const FillMode& SceneNode::GetFillMode()
{
    // attempt to perform a lazy update, if the parent's fill mode has changed
    // if the fill mode is not the same as our parent and we haven't set it
    // directly, then update it from the parent
    if (m_parent && m_fillMode != m_parent->GetFillMode() && !m_localFillMode)
    {
        m_fillMode = m_parent->GetFillMode();
    }

    return m_fillMode;
}

void SceneNode::SetAlphaTestMode(const AlphaTestMode& alphaTestMode)
{
    // save alpha test mode locally
    m_alphaTestMode = alphaTestMode;
    m_localAlphaTestMode = true;
}

const AlphaTestMode& SceneNode::GetAlphaTestMode()
{
    // attempt to perform a lazy update
    // if the alpha test mode is not the same as our parent and we haven't set it
    // directly, then update it from the parent
    if (m_parent && m_alphaTestMode != m_parent->GetAlphaTestMode() && !m_localAlphaTestMode)
    {
        m_alphaTestMode = m_parent->GetAlphaTestMode();
    }

    return m_alphaTestMode;
}

void SceneNode::SetDepthBufferWriteMode(const DepthBufferWriteMode& depthBufferWriteMode)
{
    // save depth buffer write mode locally
    m_depthBufferWriteMode = depthBufferWriteMode;
    m_localDepthBufferWriteMode = true;
}

const DepthBufferWriteMode& SceneNode::GetDepthBufferWriteMode()
{
    // attempt to perform a lazy update
    // if the depth buffer write mode is not the same as our parent
    // and we haven't set it directly, then update it from the parent
    if (m_parent && m_depthBufferWriteMode != m_parent->GetDepthBufferWriteMode() && !m_localDepthBufferWriteMode)
    {
        m_depthBufferWriteMode = m_parent->GetDepthBufferWriteMode();
    }
    
    return m_depthBufferWriteMode;
}

Matrix4 SceneNode::GetTransform()
{
    // performs lazy update of transform if needed
    // we do it here so it only gets updated if its actually used
    return m_transformComponent->GetTransform();
}

void SceneNode::Translate(const Vector3& translation)
{
    m_transformComponent->Translate(translation);

    // translation with respect to local coordinates
    //m_position += m_orientation * translation;

    // translation with respect to world coordinates
    //if (m_parent)
    //{
        // relative to parent
    //    m_position += (Inverse(m_parent->GetRelativeOrientation()) * translation) / m_parent->GetRelativeScale();
    //}
    //else
    //{
    //    m_position += translation;
    //}
}

void SceneNode::Translate(float x, float y, float z)
{
    Translate(Vector3(x, y, z));
}

void SceneNode::Rotate(const Quaternion& rotation)
{
    m_transformComponent->Rotate(rotation);
}

void SceneNode::Rotate(const Vector3& axis, float angle)
{
    Rotate(FromAxisAngle(axis, angle));
}

void SceneNode::Pitch(float angle)
{
    Rotate(Vector3::UnitX(), angle);
}

void SceneNode::Yaw(float angle)
{
    Rotate(Vector3::UnitY(), angle);
}

void SceneNode::Roll(float angle)
{
    Rotate(Vector3::UnitZ(), angle);
}

bool SceneNode::IsDirty()
{
    return m_requiresUpdate;
}

bool SceneNode::IsTransformDirty()
{
    return m_updateTransform;
}

void SceneNode::Update(uint32_t time)
{
    m_transformComponent->Update(time);

    EntityContainer::iterator entityIter;
    for (entityIter = m_entities.begin(); entityIter != m_entities.end(); ++entityIter)
    {
        (*entityIter)->Update(time);
    }
    
    // give children chance to update
    std::vector<SceneNode*>::iterator nodeIter;
    for (nodeIter = m_childNodes.begin(); nodeIter != m_childNodes.end(); ++nodeIter)
    {
        (*nodeIter)->Update(time);
    }

    // reset the dirty flag, but be sure not to change dirty flag for children
    ResetDirty(false);
}

void SceneNode::MarkDirty(bool setChildren)
{
    m_requiresUpdate = true;

    if (setChildren)
    {
        // all children will need the same dirty flag set
        // so the update cycle will process them
        std::vector<SceneNode*>::iterator iter;
        for (iter = m_childNodes.begin(); iter != m_childNodes.end(); ++iter)
        {
            (*iter)->MarkDirty(setChildren);
        }
    }

}

void SceneNode::ResetDirty(bool resetChildren)
{
    m_requiresUpdate = false;

    if (resetChildren)
    {
        // notify children of the dirty flag change
        std::vector<SceneNode*>::iterator iter;
        for (iter = m_childNodes.begin(); iter != m_childNodes.end(); ++iter)
        {
            (*iter)->ResetDirty(resetChildren);
        }
    }
}

void SceneNode::MarkTransformDirty(bool setChildren)
{
    m_updateTransform = true;

    if (setChildren)
    {
        // all children will need the same dirty flag set
        // so the update cycle will process them
        std::vector<SceneNode*>::iterator iter;
        for (iter = m_childNodes.begin(); iter != m_childNodes.end(); ++iter)
        {
            (*iter)->MarkTransformDirty(setChildren);
        }
    }
}

void SceneNode::ResetTransformDirty(bool resetChildren)
{
    m_updateTransform = false;

    if (resetChildren)
    {
        // notify children of the dirty flag change
        std::vector<SceneNode*>::iterator iter;
        for (iter = m_childNodes.begin(); iter != m_childNodes.end(); ++iter)
        {
            (*iter)->ResetTransformDirty(resetChildren);
        }
    }
}