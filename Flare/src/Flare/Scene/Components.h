#pragma once

#include "SceneCamera.h"
// #include "ScriptableEntity.h"
#include <Flare/Core/UUID.h>
#include <Flare/Renderer/Texture.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Flare
{
	/*UUID component*/
	struct IDComponent
	{
		UUID ID;

		IDComponent() = default;
		IDComponent(const IDComponent&) = default;
	};


	/*tag Component (default-component for every objects)*/
	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}
	};

	/*Transfroms component (defautl-component for every objects)*/
	struct TransformComponent 
	{
		glm::vec3 Translation = {0.0f, 0.0f, 0.0f};
		glm::vec3 Rotation = {0.0f, 0.0f, 0.0f};
		glm::vec3 Scale = {1.0f, 1.0f, 1.0f};


		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3 translation)
			:Translation(translation) {}

		glm::mat4 GetTransform() const
		{
			/*
			glm::mat4 rotation = 
			  glm::rotate(glm::mat4(1.0f), Rotation.x, { 1, 0, 0 })
			* glm::rotate(glm::mat4(1.0f), Rotation.y, { 0, 1, 0 })
			* glm::rotate(glm::mat4(1.0f), Rotation.z, { 0, 0, 1 });
			*/
			glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

			return glm::translate(glm::mat4(1.0f), Translation)
				* rotation
				* glm::scale(glm::mat4(1.0f), Scale);
		}
		
	};

	/*sprite Renderer*/
	struct SpriteRendererComponent
	{
		glm::vec4 Color{ 1.0f,1.0f, 1.0f,1.0f };
		Ref<Texture2D> Texture;
		float TilingFactor = 1.0f;

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color)
			:Color(color) {}
	};

	/*Camera*/
	struct CameraComponent
	{
		SceneCamera Camera;
		bool Primary = true; 
		bool FixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};

	/*Native Script - currenlty not work*/
	class ScriptableEntity; // forward declartion
	struct NativeScriptComponent
	{
		ScriptableEntity* Instance = nullptr;
		ScriptableEntity*(*InstantiateScript)(); //function pointer.
		void(*DestroyScript)(NativeScriptComponent*);


		template<typename T>
		void Bind()
		{
			InstantiateScript = []() {  return  static_cast<ScriptableEntity*>( new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr;};

		}
	};


	/****************************PHYSICS-COMPONENTES*****************************************/

	struct Rigidbody2DComponent
	{
		enum class BodyType {Static = 0, Dynamic, Kinematic};
		BodyType Type = BodyType::Static;
		bool FixedRotation = false;

		//storage for runtime
		void* RuntimeBody = nullptr;

		Rigidbody2DComponent() = default;
		Rigidbody2DComponent(const Rigidbody2DComponent&) = default;
	};

	struct BoxCollider2DComponent
	{
		glm::vec2 Offset = {0.0f, 0.0f};
		glm::vec2 Size = {0.5f, 0.5f};

		float Density = 1.0f;
		float Friction = 0.5f;
		float Restitution = 0.0f;
		float RestitutionThreshold = 0.5f;

		//storage for runtime
		void* RuntimeFixture = nullptr;

		BoxCollider2DComponent() = default;
		BoxCollider2DComponent(const BoxCollider2DComponent&) = default;
	};


    
}
