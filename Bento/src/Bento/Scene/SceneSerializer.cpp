#pragma once
#include "Bentopch.h"
#include "SceneSerializer.h"
#include "Entity.h"
#include "Components.h"

#include <yaml-cpp/yaml.h>

namespace YAML {

	template<>
	struct convert<glm::vec3> {

		static Node encode(const glm::vec3& rhs) {

			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			return node;
		}

		static bool decode(const Node& node, glm::vec3& rhs) {

			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}

	};
	template<>
	struct convert<glm::vec4> {

		static Node encode(const glm::vec4& rhs) {

			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			return node;
		}

		static bool decode(const Node& node, glm::vec4& rhs) {

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

	SceneSerializer::SceneSerializer(const Ref<Scene>& scene)
		: m_Scene(scene)
	{
	}

	static void SerializeEntity(YAML::Emitter& out, Entity entity) {

		out << YAML::BeginMap; // Entity
		out << YAML::Key << "Entity" << YAML::Value << (uint32_t)entity;
		

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
			out << YAML::Key << "ProjectionType" << YAML::Value << camera.GetProjectionType();
			out << YAML::Key << "PerspectiveFOV" << YAML::Value << camera.GetPerspectiveFOV();
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

		if (entity.HasComponent<SpriteRendererComponent>()) {

			out << YAML::Key << "SpriteRendererComponent";
			out << YAML::BeginMap; // SpriteRendererComponent

			auto& color = entity.GetComponent<SpriteRendererComponent>().Color;
			out << YAML::Key << "Color" << YAML::Value << color;

			out << YAML::EndMap; // SpriteRendererComponent

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

				uint64_t uuid = entity["Entity"].as<uint64_t>(); // TODO

				std::string name;
				auto tagComponent = entity["TagComponent"];
				if (tagComponent)
					name = tagComponent["Tag"].as<std::string>();

				BENTO_CORE_TRACE("Deserialized entity with ID = {0}, name = {1}", uuid, name);

				Entity deserializedEntity = m_Scene->CreateEntity(name);

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

				}

				auto cameraComponent = entity["CameraComponent"];
				auto camera = cameraComponent["Camera"];
				if (cameraComponent && camera) {

					deserializedEntity.AddComponent<CameraComponent>();
					auto& camComponent = deserializedEntity.GetComponent<CameraComponent>();

					camComponent.Camera.SetProjectionType(camera["ProjectionType"].as<uint32_t>());
					camComponent.Camera.SetPerspectiveFOV(camera["PerspectiveFOV"].as<float>());
					camComponent.Camera.SetPerspectiveNearClip(camera["PerspectiveNear"].as<float>());
					camComponent.Camera.SetPerspectiveFarClip(camera["PerspectiveFar"].as<float>());
					camComponent.Camera.SetOrthographicSize(camera["OrthographicSize"].as<float>());
					camComponent.Camera.SetOrthographicNearClip(camera["OrthographicNear"].as<float>());
					camComponent.Camera.SetOrthographicFarClip(camera["OrthographicFar"].as<float>());

					camComponent.Primary = cameraComponent["Primary"].as<bool>();
					camComponent.FixedAspectRatio = cameraComponent["FixedAspectRatio"].as<bool>();

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