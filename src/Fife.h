/**********************************************************************
*	Filename: Fife.h
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
#ifndef FIFE_H_
#define FIFE_H_

// provided as convenience so a user only has to 
// include a single header to use the engine

// misc, some of these may move into subdirectories
#include "StdIncludes.h"
#include "Stdint.h"
#include "Engine.h"
#include "SharedPtr.h"
#include "Color.h"

// entity
#include "IEntity.h"
#include "IComponent.h"
#include "RenderComponent.h"
#include "Visual.h"         // TODO - this should be removed at some point

// filesystem
#include "filesystem/IFileSystem.h"
#include "filesystem/IPath.h"
#include "filesystem/Path.h"        // TODO - should this be here?

// geometry
#include "geometry/AxisAlignedBoundingBox.h"
#include "geometry/Dimension.h"
#include "geometry/Plane.h"
#include "geometry/Rect.h"
#include "geometry/Sphere.h"

// graphics
#include "graphics/ImageEnums.h"        // TODO - does this need to be included?
#include "graphics/ImageFwd.h"
#include "graphics/ImageManager.h"
#include "graphics/IImageLoader.h"
#include "graphics/IIndexBuffer.h"
#include "graphics/IVertexBuffer.h"
#include "graphics/ITexture.h"
#include "graphics/TextureEnums.h"
#include "graphics/TextureFwd.h"
#include "graphics/TextureManager.h"
#include "graphics/Vertex.h"
#include "graphics/VertexData.h"
#include "graphics/VertexIndexBufferEnums.h"

// gui


// inputsystem
#include "inputsystem/IInputSystem.h"
#include "inputsystem/KeyCodes.h"
#include "inputsystem/keyboard/IKeyEvent.h"
#include "inputsystem/keyboard/IKeyListener.h"
#include "inputsystem/mouse/IMouseEvent.h"
#include "inputsystem/mouse/IMouseListener.h"

// math
#include "math/MathUtil.h"
#include "math/Matrix4.h"
#include "math/Quaternion.h"
#include "math/Randomizer.h"
#include "math/Vector2.h"
#include "math/Vector3.h"

// particlesystem
#include "particlesystem/ParticleSystem.h"
#include "particlesystem/ParticleEmitter.h"
#include "particlesystem/IParticleEffect.h"
#include "particlesystem/ParticleColorChangeEffect.h"
#include "particlesystem/ParticleColorRandomizerEffect.h"
#include "particlesystem/ParticleFadeEffect.h"
#include "particlesystem/ParticleVelocityEffect.h"

// rendersystem
#include "rendersystem/IRenderSystem.h"
#include "rendersystem/RenderEnums.h"
#include "rendersystem/RenderSystemTypes.h"
#include "rendersystem/BlendingMode.h"
#include "rendersystem/CullMode.h"
#include "rendersystem/PolygonWindingMode.h"
#include "rendersystem/FillMode.h"
#include "rendersystem/AlphaTestMode.h"

// scene
#include "scene/SceneManager.h"
#include "scene/SceneNode.h"
#include "scene/Camera.h"
#include "scene/IAnimatedFrame.h"
#include "scene/IAnimation.h"
#include "scene/IMaterial.h"
#include "scene/ISpriteSheet.h"
#include "scene/Renderable.h"
#include "scene/Billboard.h"    // should this be here?
#include "scene/Material.h"     // should this be here?

// timer
#include "timer/Timer.h"

// windowsystem
#include "windowsystem/IWindowSystem.h"
#include "windowsystem/IWindowSystemEventListener.h"
#include "windowsystem/WindowSystemTypes.h"

#endif
