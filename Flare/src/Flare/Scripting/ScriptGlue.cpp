#include "ScriptGlue.h"
#include "ScriptEngine.h"

#include <Flare/Core/Log.h>
#include "Flare/Core/UUID.h"
#include "Flare/Core/KeyCodes.h"
#include "Flare/Core/Input.h"

#include "Flare/Scene/Scene.h"
#include "Flare/Scene/Entity.h"

#include "mono/metadata/object.h"
#include "mono/metadata/reflection.h"

#include "box2d/b2_body.h"

#include <glm/glm.hpp>
// #include <fmt/format.h>

// Specialize fmt::formatter for glm::vec3
template <>
struct fmt::formatter<glm::vec3> {
    // Parse format specifier (not used here, so just return the context)
    constexpr auto parse(fmt::format_parse_context& ctx) {
        return ctx.begin();
    }

    // Format glm::vec3 as "(x, y, z)"
    template <typename FormatContext>
    auto format(const glm::vec3& vec, FormatContext& ctx) {
        return fmt::format_to(ctx.out(), "({}, {}, {})", vec.x, vec.y, vec.z);
    }
};

namespace Flare{

// #define FL_ADD_INTERNAL_CALL(Name) mono_add_internal_call("Flare.InternalCalls::" #Name, Name)

    
	static std::unordered_map<MonoType*, std::function<bool(Entity)>> s_EntityHasComponentFuncs;

	#define HZ_ADD_INTERNAL_CALL(Name) mono_add_internal_call("Flare.InternalCalls::" #Name,(const void*)(Name))
	
		static void NativeLog(MonoString* string, int parameter)
		{
			char* cStr = mono_string_to_utf8(string);
			std::string str(cStr);
			mono_free(cStr);
			std::cout << str << ", " << parameter << std::endl;
		}
	
		static void NativeLog_Vector(glm::vec3* parameter, glm::vec3* outResult)
		{
			LOG_WARN("Value: {0}", *parameter);
			*outResult = glm::normalize(*parameter);
		}
	
		static float NativeLog_VectorDot(glm::vec3* parameter)
		{
			LOG_WARN("Value: {0}", *parameter);
			return glm::dot(*parameter, *parameter);
		}
	
		static bool Entity_HasComponent(UUID entityID, MonoReflectionType* componentType)
		{
			Scene* scene = ScriptEngine::GetSceneContext();
			// HZ_CORE_ASSERT(scene);
			Entity entity = scene->GetEntityByUUID(entityID);
			// HZ_CORE_ASSERT(entity);
	
			MonoType* managedType = mono_reflection_type_get_type(componentType);
			// HZ_CORE_ASSERT(s_EntityHasComponentFuncs.find(managedType) != s_EntityHasComponentFuncs.end());
			return s_EntityHasComponentFuncs.at(managedType)(entity);
		}
	
		static void TransformComponent_GetTranslation(UUID entityID, glm::vec3* outTranslation)
		{
			Scene* scene = ScriptEngine::GetSceneContext();
			// HZ_CORE_ASSERT(scene);
			Entity entity = scene->GetEntityByUUID(entityID);
			// HZ_CORE_ASSERT(entity);
	
			*outTranslation = entity.GetComponent<TransformComponent>().Translation;
		}
	
		static void TransformComponent_SetTranslation(UUID entityID, glm::vec3* translation)
		{
			Scene* scene = ScriptEngine::GetSceneContext();
			// HZ_CORE_ASSERT(scene);
			Entity entity = scene->GetEntityByUUID(entityID);
			// HZ_CORE_ASSERT(entity);
	
			entity.GetComponent<TransformComponent>().Translation = *translation;
		}
	
		static void Rigidbody2DComponent_ApplyLinearImpulse(UUID entityID, glm::vec2* impulse, glm::vec2* point, bool wake)
		{
			Scene* scene = ScriptEngine::GetSceneContext();
			// HZ_CORE_ASSERT(scene);
			Entity entity = scene->GetEntityByUUID(entityID);
			// HZ_CORE_ASSERT(entity);
	
			auto& rb2d = entity.GetComponent<Rigidbody2DComponent>();
			b2Body* body = (b2Body*)rb2d.RuntimeBody;
			body->ApplyLinearImpulse(b2Vec2(impulse->x, impulse->y), b2Vec2(point->x, point->y), wake);
		}
	
		static void Rigidbody2DComponent_ApplyLinearImpulseToCenter(UUID entityID, glm::vec2* impulse, bool wake)
		{
			Scene* scene = ScriptEngine::GetSceneContext();
			// HZ_CORE_ASSERT(scene);
			Entity entity = scene->GetEntityByUUID(entityID);
			// HZ_CORE_ASSERT(entity);
	
			auto& rb2d = entity.GetComponent<Rigidbody2DComponent>();
			b2Body* body = (b2Body*)rb2d.RuntimeBody;
			body->ApplyLinearImpulseToCenter(b2Vec2(impulse->x, impulse->y), wake);
		}
		
		static bool Input_IsKeyDown(KeyCode keycode)
		{
			return Input::IsKeyPressed(keycode);
		}
		
	
		template<typename... Component>
		static void RegisterComponent()
		{
			([]()
			{
				LOG_TRACE("Registering component {}", typeid(Component).name());
				std::string_view typeName = typeid(Component).name();
				size_t pos = typeName.find_last_of(':');
				std::string_view structName = typeName.substr(pos + 1);
				std::string managedTypename = fmt::format("Flare.{}", structName);

	
				MonoType* managedType = mono_reflection_type_from_name(managedTypename.data(), ScriptEngine::GetCoreAssemblyImage());
				if (!managedType)
				{
					LOG_ERROR("Could not find component type {}", managedTypename);
					return;
				}
				s_EntityHasComponentFuncs[managedType] = [](Entity entity) { return entity.HasComponent<Component>(); };
			}(), ...);
		}
	
		template<typename... Component>
		static void RegisterComponent(ComponentGroup<Component...>)
		{
			RegisterComponent<Component...>();
		}
	
		void ScriptGlue::RegisterComponents()
		{
			RegisterComponent(AllComponents{});
		}
	
		void ScriptGlue::RegisterFunctions()
		{
			HZ_ADD_INTERNAL_CALL(NativeLog);
			HZ_ADD_INTERNAL_CALL(NativeLog_Vector);
			HZ_ADD_INTERNAL_CALL(NativeLog_VectorDot);
	
			HZ_ADD_INTERNAL_CALL(Entity_HasComponent);
			HZ_ADD_INTERNAL_CALL(TransformComponent_GetTranslation);
			HZ_ADD_INTERNAL_CALL(TransformComponent_SetTranslation);
			
			HZ_ADD_INTERNAL_CALL(Rigidbody2DComponent_ApplyLinearImpulse);
			HZ_ADD_INTERNAL_CALL(Rigidbody2DComponent_ApplyLinearImpulseToCenter);
	
			HZ_ADD_INTERNAL_CALL(Input_IsKeyDown);
		}

}