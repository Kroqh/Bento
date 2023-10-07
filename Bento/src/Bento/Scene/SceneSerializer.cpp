#pragma once
#include "Bentopch.h"
#include "SceneSerializer.h"
#include "Entity.h"
#include "Components.h"
#include "Bento/Renderer/Texture.h"

#include <yaml-cpp/yaml.h>

namespace YAML {

	template<>
	struct convert<glm::vec2>
	{
		static Node encode(const glm::vec2& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			return node;
		}

		static bool decode(const Node& node, glm::vec2& rhs)
		{
			if (!node.IsSequence() || node.size() != 2)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec3>
	{
		static Node encode(const glm::vec3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			return node;
		}

		static bool decode(const Node& node, glm::vec3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec4>
	{
		static Node encode(const glm::vec4& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			return node;
		}

		static bool decode(const Node& node, glm::vec4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};
	

}

namespace Bento {

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec2& v) {

		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << YAML::EndSeq;
		return out;

	}
	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v) {

		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
		return out;

	}
	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v) {

		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
		return out;

	}

	static std::string RigidBody2DBodyTypeToString(Rigidbody2DComponent::BodyType bodyType) {

		switch (bodyType)
		{
		case Bento::Rigidbody2DComponent::BodyType::Static: return "Static";
		case Bento::Rigidbody2DComponent::BodyType::Kinematic: return "Kinematic";
		case Bento::Rigidbody2DComponent::BodyType::Dynamic: return "Dynamic";
		}

		BENTO_CORE_ASSERT(false, "Unknown body type!");
		return {};
	}

	static Rigidbody2DComponent::BodyType StringToRigidBody2DBodyType(const std::string& bodyTypeString) {

		if (bodyTypeString == "Static") return Rigidbody2DComponent::BodyType::Static;
		if (bodyTypeString == "Kinematic") return Rigidbody2DComponent::BodyType::Kinematic;
		if (bodyTypeString == "Dynamic") return Rigidbody2DComponent::BodyType::Dynamic;

		BENTO_CORE_ASSERT(false, "Unknown body type!");
		return {};
	}

	SceneSerializer::SceneSerializer(const Ref<Scene>& scene)
		: m_Scene(scene)
	{
	}

	static void SerializeEntity(YAML::Emitter& out, Entity entity) {

		BENTO_CORE_ASSERT(entity.HasComponent<IDComponent>());

		out << YAML::BeginMap; // Entity
		out << YAML::Key << "Entity" << YAML::Value << entity.GetUUID();
		

		if (entity.HasComponent<TagComponent>()) {

			out << YAML::Key << "TagComponent";
			out << YAML::BeginMap; // TagComponent

			auto& tag = entity.GetComponent<TagComponent>().Tag;
			out << YAML::Key << "Tag" << YAML::Value << tag;

			out << YAML::EndMap; // TagComponent

		}

		if (entity.HasComponent<TransformComponent>()) {

			out << YAML::Key << "TransformComponent";
			out << YAML::BeginMap; // TransformComponent

			auto& tc = entity.GetComponent<TransformComponent>();
			out << YAML::Key << "Position" << YAML::Value << tc.Position;
			out << YAML::Key << "Rotation" << YAML::Value << tc.Rotation;
			out << YAML::Key << "Scale" << YAML::Value << tc.Scale;

			out << YAML::EndMap; // TransformComponent

		}

		if (entity.HasComponent<CameraComponent>()) {
			out << YAML::Key << "CameraComponent";
			out << YAML::BeginMap; // CameraComponent

			auto& cameraComponent = entity.GetComponent<CameraComponent>();
			auto& camera = cameraComponent.Camera;

			out << YAML::Key << "Camera" << YAML::Value;
			out << YAML::BeginMap; // Camera
			out << YAML::Key << "ProjectionType" << YAML::Value << (uint32_t)camera.GetProjectionType();
			out << YAML::Key << "PerspectiveFOV" << YAML::Value << camera.GetPerspectiveVerticalFOV();
			out << YAML::Key << "PerspectiveNear" << YAML::Value << camera.GetPerspectiveNearClip();
			out << YAML::Key << "PerspectiveFar" << YAML::Value << camera.GetPerspectiveFarClip();
			out << YAML::Key << "OrthographicSize" << YAML::Value << camera.GetOrthographicSize();
			out << YAML::Key << "OrthographicNear" << YAML::Value << camera.GetOrthographicNearClip();
			out << YAML::Key << "OrthographicFar" << YAML::Value << camera.GetOrthographicFarClip();
			out << YAML::EndMap; // Camera

			out << YAML::Key << "Primary" << YAML::Value << cameraComponent.Primary;
			out << YAML::Key << "FixedAspectRatio" << YAML::Value << cameraComponent.FixedAspectRatio;

			out << YAML::EndMap; // CameraComponent
		}

		if (entity.HasComponent<ScriptComponent>()) {

			out << YAML::Key << "ScriptComponent";
			out << YAML::BeginMap; // ScriptComponent

			auto& sc = entity.GetComponent<ScriptComponent>();
			out << YAML::Key << "Name" << YAML::Value << sc.Name;

			out << YAML::EndMap; // ScriptComponent

		}

		if (entity.HasComponent<SpriteRendererComponent>()) {

			out << YAML::Key << "SpriteRendererComponent";
			out << YAML::BeginMap; // SpriteRendererComponent

			auto& src = entity.GetComponent<SpriteRendererComponent>();
			out << YAML::Key << "Color" << YAML::Value << src.Color;

			if(src.Texture)
				out << YAML::Key << "TexturePath" << YAML::Value << src.Texture->GetTexturePath();

			out << YAML::Key << "TilingFactor" << YAML::Value << src.TilingFactor;

			out << YAML::EndMap; // SpriteRendererComponent

		}

		if (entity.HasComponent<CircleRendererComponent>()) {

			out << YAML::Key << "CircleRendererComponent";
			out << YAML::BeginMap; // CircleRendererComponent

			auto& crc = entity.GetComponent<CircleRendererComponent>();
			out << YAML::Key << "Color" << YAML::Value << crc.Color;
			out << YAML::Key << "Thickness" << YAML::Value << crc.Thickness;
			out << YAML::Key << "Fade" << YAML::Value << crc.Fade;

			out << YAML::EndMap; // CircleRendererComponent

		}

		if (entity.HasComponent<Rigidbody2DComponent>()) {

			out << YAML::Key << "Rigidbody2DComponent";
			out << YAML::BeginMap; // Rigidbody2DComponent

			auto& rb2d = entity.GetComponent<Rigidbody2DComponent>();
			out << YAML::Key << "FixedRotation" << YAML::Value << rb2d.FixedRotation;
			out << YAML::Key << "BodyType" << YAML::Value << RigidBody2DBodyTypeToString(rb2d.Type);
			out << YAML::Key << "GravityScale" << YAML::Value << rb2d.gravityScale;

			out << YAML::EndMap; // Rigidbody2DComponent

		}

		if(entity.HasComponent<BoxCollider2DComponent>()) {

			out << YAML::Key << "BoxCollider2DComponent";
			out << YAML::BeginMap; // BoxCollider2DComponent

			auto& bc2d = entity.GetComponent<BoxCollider2DComponent>();
			out << YAML::Key << "Size" << YAML::Value << bc2d.Size;
			out << YAML::Key << "Offset" << YAML::Value << bc2d.Offset;
			out << YAML::Key << "Density" << YAML::Value << bc2d.Density;
			out << YAML::Key << "Friction" << YAML::Value << bc2d.Friction;
			out << YAML::Key << "Restitution" << YAML::Value << bc2d.Restitution;
			out << YAML::Key << "RestitutionThreshold" << YAML::Value << bc2d.RestitutionThreshold;

			out << YAML::EndMap; // BoxCollider2DComponent

		}

		if (entity.HasComponent<CircleCollider2DComponent>()) {

			out << YAML::Key << "CircleCollider2DComponent";
			out << YAML::BeginMap; // CircleCollider2DComponent

			auto& cc2d = entity.GetComponent<CircleCollider2DComponent>();
			out << YAML::Key << "Radius" << YAML::Value << cc2d.Radius;
			out << YAML::Key << "Offset" << YAML::Value << cc2d.Offset;
			out << YAML::Key << "Density" << YAML::Value << cc2d.Density;
			out << YAML::Key << "Friction" << YAML::Value << cc2d.Friction;
			out << YAML::Key << "Restitution" << YAML::Value << cc2d.Restitution;
			out << YAML::Key << "RestitutionThreshold" << YAML::Value << cc2d.RestitutionThreshold;

			out << YAML::EndMap; // CircleCollider2DComponent

		}

		out << YAML::EndMap; // Entity
	}

	void SceneSerializer::Serialize(const std::string& filepath)
	{
		YAML::Emitter out;

		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << "Untitled Scene";
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;

		m_Scene->m_Registry.each([&](auto entityID) {

			Entity entity = { entityID, m_Scene.get() };
			if (!entity)
				return;

			SerializeEntity(out, entity);

			});
		out << YAML::EndSeq;
		out << YAML::EndMap;

		std::ofstream fout(filepath);
		fout << out.c_str();
	}

	void SceneSerializer::SerializeRuntime(const std::string& filepath)
	{
	}

	bool SceneSerializer::DeSerialize(const std::string& filepath)
	{
		std::ifstream stream(filepath);
		std::stringstream strStream;
		strStream << stream.rdbuf();

		YAML::Node data = YAML::Load(strStream.str());
		if (!data["Scene"])
			return false;

		std::string sceneName = data["Scene"].as<std::string>();
		BENTO_CORE_TRACE("Deserializing scene '{0}", sceneName);

		auto entities = data["Entities"];
		if (entities) {
			for (auto entity : entities) {

				uint64_t uuid = entity["Entity"].as<uint64_t>();

				std::string name;
				auto tagComponent = entity["TagComponent"];
				if (tagComponent)
					name = tagComponent["Tag"].as<std::string>();

				BENTO_CORE_TRACE("Deserialized entity with ID = {0}, name = {1}", uuid, name);

				Entity deserializedEntity = m_Scene->CreateEntityWithUUID(uuid, name);

				auto transformComponent = entity["TransformComponent"];
				if (transformComponent) {

					// Entities always have transforms

					auto& tc = deserializedEntity.GetComponent<TransformComponent>();
					tc.Position = transformComponent["Position"].as<glm::vec3>();
					tc.Rotation = transformComponent["Rotation"].as<glm::vec3>();
					tc.Scale = transformComponent["Scale"].as<glm::vec3>();

				}

				auto spriteRendererCompoent = entity["SpriteRendererComponent"];
				if (spriteRendererCompoent) {
					deserializedEntity.AddComponent<SpriteRendererComponent>();
					auto& src = deserializedEntity.GetComponent<SpriteRendererComponent>();
					src.Color = spriteRendererCompoent["Color"].as<glm::vec4>();
					if(spriteRendererCompoent["TexturePath"])
					{
						src.Texture = Texture2D::Create(spriteRendererCompoent["TexturePath"].as<std::string>());
					}
					src.TilingFactor = spriteRendererCompoent["TilingFactor"].as<float>();

				}

				auto circleRendererComponent = entity["CircleRendererComponent"];
				if (circleRendererComponent) {
					deserializedEntity.AddComponent<CircleRendererComponent>();
					auto& crc = deserializedEntity.GetComponent<CircleRendererComponent>();
					crc.Color = circleRendererComponent["Color"].as<glm::vec4>();
					crc.Thickness = circleRendererComponent["Thickness"].as<float>();
					crc.Fade = circleRendererComponent["Fade"].as<float>();

				}



				auto cameraComponent = entity["CameraComponent"];
				auto camera = cameraComponent["Camera"];
				if (cameraComponent && camera) {

					deserializedEntity.AddComponent<CameraComponent>();
					auto& camComponent = deserializedEntity.GetComponent<CameraComponent>();

					camComponent.Camera.SetProjectionType((SceneCamera::ProjectionType)camera["ProjectionType"].as<uint32_t>());
					camComponent.Camera.SetPerspectiveVerticalFOV(camera["PerspectiveFOV"].as<float>());
					camComponent.Camera.SetPerspectiveNearClip(camera["PerspectiveNear"].as<float>());
					camComponent.Camera.SetPerspectiveFarClip(camera["PerspectiveFar"].as<float>());
					camComponent.Camera.SetOrthographicSize(camera["OrthographicSize"].as<float>());
					camComponent.Camera.SetOrthographicNearClip(camera["OrthographicNear"].as<float>());
					camComponent.Camera.SetOrthographicFarClip(camera["OrthographicFar"].as<float>());

					camComponent.Primary = cameraComponent["Primary"].as<bool>();
					camComponent.FixedAspectRatio = cameraComponent["FixedAspectRatio"].as<bool>();

				}

				auto scriptComponent = entity["ScriptComponent"];
				if (scriptComponent) {
					auto& sc = deserializedEntity.AddComponent<ScriptComponent>();
					sc.Name = scriptComponent["Name"].as<std::string>();
				}

				auto rigidbody2DComponent = entity["Rigidbody2DComponent"];
				if (rigidbody2DComponent) {
					auto& rb2d = deserializedEntity.AddComponent<Rigidbody2DComponent>();
					rb2d.FixedRotation = rigidbody2DComponent["FixedRotation"].as<bool>();
					rb2d.Type = StringToRigidBody2DBodyType(rigidbody2DComponent["BodyType"].as<std::string>());
					rb2d.gravityScale = rigidbody2DComponent["GravityScale"].as<float>();
				}

				auto boxCollider2DComponent = entity["BoxCollider2DComponent"];
				if (boxCollider2DComponent) {
					auto& bc2d = deserializedEntity.AddComponent<BoxCollider2DComponent>();
					bc2d.Size = boxCollider2DComponent["Size"].as<glm::vec2>();
					bc2d.Offset = boxCollider2DComponent["Offset"].as<glm::vec2>();
					bc2d.Density = boxCollider2DComponent["Density"].as<float>();
					bc2d.Friction = boxCollider2DComponent["Friction"].as<float>();
					bc2d.Restitution = boxCollider2DComponent["Restitution"].as<float>();
					bc2d.RestitutionThreshold = boxCollider2DComponent["RestitutionThreshold"].as<float>();
				}

				auto circleCollider2DComponent = entity["CircleCollider2DComponent"];
				if (circleCollider2DComponent) {
					auto& cc2d = deserializedEntity.AddComponent<CircleCollider2DComponent>();
					cc2d.Radius = circleCollider2DComponent["Radius"].as<float>();
					cc2d.Offset = circleCollider2DComponent["Offset"].as<glm::vec2>();
					cc2d.Density = circleCollider2DComponent["Density"].as<float>();
					cc2d.Friction = circleCollider2DComponent["Friction"].as<float>();
					cc2d.Restitution = circleCollider2DComponent["Restitution"].as<float>();
					cc2d.RestitutionThreshold = circleCollider2DComponent["RestitutionThreshold"].as<float>();
				}
			}
		}
	}

	bool SceneSerializer::DeSerializeRuntime(const std::string& filepath)
	{
		// Not implemented
		BENTO_CORE_ASSERT("DeSerializeRuntime not implemented",false);
		return false;
	}

}