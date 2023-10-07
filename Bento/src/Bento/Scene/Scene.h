#pragma once


#include "Bento/Core/UUID.h"
#include "Bento/Core/Timestep.h"
#include "Bento/Renderer/EditorCamera.h"
#include "Bento/Scripting/ScriptGlue.h"

#include <entt.hpp>



class EditorCamera;

class b2World;

#ifdef __cplusplus
extern "C" {
#endif

	class ma_engine;

#ifdef __cplusplus
}
#endif


namespace Bento {

	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		static Ref<Scene> Copy(Ref<Scene> other);

		Entity CreateEntity(const std::string& name = std::string());
		Entity CreateEntityWithUUID(UUID uuid, const std::string& name = std::string());
		Entity GetEntity(UUID uuid);

		void DestroyEntity(Entity entity);
		void DuplicateEntity(Entity entity);

		void OnRuntimeStart();
		void OnRuntimeStop();

		void OnUpdateRuntime(Timestep ts);
		void OnUpdateEditor(Timestep ts, EditorCamera& camera);
		void OnViewportResize(uint32_t width, uint32_t height);

		void OnRenderOverlay(EditorCamera& camera);

		Entity GetPrimaryCameraEntity();

		bool IsRunning() const { return m_IsRunning; }

	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);

	private:
		entt::registry m_Registry;
		std::unordered_map<UUID, entt::entity> m_EntityMap;

		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
		bool m_IsRunning = false;

		b2World* m_PhysicsWorld = nullptr;
		ma_engine* m_AudioEngine;

		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;

	};


}