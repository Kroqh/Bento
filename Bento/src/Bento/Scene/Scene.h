#pragma once

#include <entt.hpp>

#include "Bento/Core/Timestep.h"

namespace Bento {

	class Entity;

	class Scene {

	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name);

		void DestroyEntity(Entity entity);



		void OnUpdate(Timestep ts);
	private:
		entt::registry m_Registry;
		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;

	};

}