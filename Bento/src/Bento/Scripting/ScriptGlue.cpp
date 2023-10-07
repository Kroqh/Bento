#include "Bentopch.h"
#include "Bento.h"

#include "ScriptGlue.h"
#include "ScriptEngine.h"

#include "mono/jit/jit.h"
#include "mono/metadata/object.h"
#include "mono/metadata/reflection.h"

// Box2D 
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_circle_shape.h>

namespace Bento {

	static std::unordered_map<MonoType*, std::function<bool(Entity)>> s_EntityHasComponentFuncs;

#define BENTO_ADD_INTERNAL_CALL(Name) mono_add_internal_call("Bento.InternalCalls::" #Name, Name)

	static bool Entity_HasComponent(UUID uuid, MonoReflectionType* componentType) {

		Scene* scene = ScriptEngine::GetSceneContext();
		BENTO_CORE_ASSERT(scene);
		Entity entity = scene->GetEntity(uuid);
		BENTO_CORE_ASSERT(entity);

		MonoType* managedType = mono_reflection_type_get_type(componentType);

		BENTO_CORE_ASSERT(s_EntityHasComponentFuncs.find(managedType) != s_EntityHasComponentFuncs.end());

		return s_EntityHasComponentFuncs.at(managedType)(entity);
	}

	static void Entity_GetName(UUID uuid, MonoString ** name) {

		Scene* scene = ScriptEngine::GetSceneContext();
		BENTO_CORE_ASSERT(scene);
		Entity entity = scene->GetEntity(uuid);
		BENTO_CORE_ASSERT(entity);
		*name = mono_string_new(mono_domain_get(), entity.GetComponent<TagComponent>().Tag.c_str());
		
	}

#pragma region TransFormComponent
	static void TransformComponent_GetPosition(UUID uuid, glm::vec3* position) {

		Scene* scene = ScriptEngine::GetSceneContext();
		Entity entity = scene->GetEntity(uuid);
		*position = entity.GetComponent<TransformComponent>().Position;
	}

	static void TransformComponent_SetPosition(UUID uuid, glm::vec3* position) {
		Scene* scene = ScriptEngine::GetSceneContext();
		Entity entity = scene->GetEntity(uuid);
		entity.GetComponent<TransformComponent>().Position = *position;

	}

	static void TransformComponent_GetRotation(UUID uuid, glm::vec3* rotation) {

		Scene* scene = ScriptEngine::GetSceneContext();
		Entity entity = scene->GetEntity(uuid);
		*rotation = entity.GetComponent<TransformComponent>().Rotation;
	}

	static void TransformComponent_SetRotation(UUID uuid, glm::vec3* rotation) {
		Scene* scene = ScriptEngine::GetSceneContext();
		Entity entity = scene->GetEntity(uuid);
		entity.GetComponent<TransformComponent>().Rotation = glm::radians(*rotation);

	}

	static void TransformComponent_GetLocalScale(UUID uuid, glm::vec3* scale) {

		Scene* scene = ScriptEngine::GetSceneContext();
		Entity entity = scene->GetEntity(uuid);
		*scale = entity.GetComponent<TransformComponent>().Scale;
	}

	static void TransformComponent_SetLocalScale(UUID uuid, glm::vec3* scale) {
		Scene* scene = ScriptEngine::GetSceneContext();
		Entity entity = scene->GetEntity(uuid);
		entity.GetComponent<TransformComponent>().Scale = *scale;

	}
#pragma endregion

#pragma region RigidBody2D
	static void Rigidbody2DComponent_GetVelocity(UUID uuid, glm::vec3* velocity) {

		Scene* scene = ScriptEngine::GetSceneContext();
		Entity entity = scene->GetEntity(uuid);
		auto& rb2d = entity.GetComponent<Rigidbody2DComponent>();
		b2Body* body = (b2Body*)rb2d.RuntimeBody;
		b2Vec2 velocityVec = body->GetLinearVelocity();
		velocity->x = velocityVec.x;
		velocity->y = velocityVec.y;
		
	}

	static void Rigidbody2DComponent_SetVelocity(UUID uuid, glm::vec3* velocity) {

		Scene* scene = ScriptEngine::GetSceneContext();
		Entity entity = scene->GetEntity(uuid);
		auto& rb2d = entity.GetComponent<Rigidbody2DComponent>();
		b2Body* body = (b2Body*)rb2d.RuntimeBody;
		b2Vec2 velocityVec = b2Vec2(velocity->x, velocity->y);
		body->SetLinearVelocity(velocityVec);
	}

	static void Rigidbody2DComponent_AddForce_Impulse(UUID uuid, glm::vec3* forceDirection) {

		// Not workint
		//Scene* scene = ScriptEngine::GetSceneContext();
		//Entity entity = scene->GetEntity(uuid);
		//auto& rb2d = entity.GetComponent<Rigidbody2DComponent>();
		//b2Body* body = (b2Body*)rb2d.RuntimeBody;
		//b2Vec2 velocityVec = b2Vec2(forceDirection->x, forceDirection->y);
		//body->SetAwake(true);
		//body->ApplyLinearImpulse(-velocityVec,body->GetWorldCenter(), true);
		
	}

	static void Rigidbody2DComponent_AddForce_Force(UUID uuid, glm::vec3* forceDirection) {

		Scene* scene = ScriptEngine::GetSceneContext();
		Entity entity = scene->GetEntity(uuid);
		auto& rb2d = entity.GetComponent<Rigidbody2DComponent>();
		b2Body* body = (b2Body*)rb2d.RuntimeBody;
		b2Vec2 velocityVec = b2Vec2(forceDirection->x, forceDirection->y);
		body->SetAwake(true);
		body->ApplyForceToCenter(velocityVec, true);
	}

#pragma endregion

	

	static void Vector3_Normalize(glm::vec3* vector) {
		glm::vec3 vec = *vector;
		*vector = glm::normalize(vec);
	}

	static void Vector3_Normalized(glm::vec3* vector) {
		*vector = glm::normalize(*vector);
	}

	static bool Input_IsKey(KeyCode keycode) {
		return Input::IsKeyPressed(keycode);
	}

	static bool Input_IsKeyDown(KeyCode keycode) {
		return Input::IsKeyDown(keycode);
	}

	template<typename ... Component>
	static void RegisterComponent() {

		([]() {
			std::string typeName = typeid(Component).name();

			size_t pos = typeName.find_last_of(':');
			std::string structName = typeName.substr(pos + 1, typeName.length() - sizeof("Component"));
			structName = structName.substr(0, structName.length() + 1 - sizeof("Component"));
			std::string managedTypeName = fmt::format("Bento.{}", structName);

			MonoType* managedType = mono_reflection_type_from_name(managedTypeName.data(), ScriptEngine::GetCoreAssemblyImage());

			if (!managedType) {
				BENTO_CORE_ERROR("Could not find component type {}", managedTypeName);
				return;
			}

			s_EntityHasComponentFuncs[managedType] = [](Entity entity) { return entity.HasComponent<Component>(); };
			}(), ...);
	}
	template<typename ... Component>
	static void RegisterComponent(ComponentGroup<Component ...>) {
		RegisterComponent<Component ...>();
	}

	void ScriptGlue::RegisterComponents()
	{
		RegisterComponent(AllComponents{});
	}

	void ScriptGlue::RegisterFunctions()
	{
		BENTO_ADD_INTERNAL_CALL(Entity_HasComponent);
		BENTO_ADD_INTERNAL_CALL(Entity_GetName);

		BENTO_ADD_INTERNAL_CALL(TransformComponent_GetPosition);
		BENTO_ADD_INTERNAL_CALL(TransformComponent_SetPosition);
		BENTO_ADD_INTERNAL_CALL(TransformComponent_GetRotation);
		BENTO_ADD_INTERNAL_CALL(TransformComponent_SetRotation);
		BENTO_ADD_INTERNAL_CALL(TransformComponent_GetLocalScale);
		BENTO_ADD_INTERNAL_CALL(TransformComponent_SetLocalScale);

		BENTO_ADD_INTERNAL_CALL(Rigidbody2DComponent_GetVelocity);
		BENTO_ADD_INTERNAL_CALL(Rigidbody2DComponent_SetVelocity);
		BENTO_ADD_INTERNAL_CALL(Rigidbody2DComponent_AddForce_Impulse);
		BENTO_ADD_INTERNAL_CALL(Rigidbody2DComponent_AddForce_Force);

		BENTO_ADD_INTERNAL_CALL(Vector3_Normalize);
		BENTO_ADD_INTERNAL_CALL(Vector3_Normalized);

		BENTO_ADD_INTERNAL_CALL(Input_IsKey);
		BENTO_ADD_INTERNAL_CALL(Input_IsKeyDown);
	}

}