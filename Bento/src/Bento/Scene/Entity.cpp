#pragma once
#include "Bentopch.h"
#include "Entity.h"

namespace Bento {



	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{
	}

}