#pragma once

#include <memory>
#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

#include "../../vendor/spdlog/include/spdlog/spdlog.h" // for codelite;
#include "../../vendor/spdlog/include/spdlog/sinks/stdout_color_sinks.h" // for codelite;


namespace Flare{
    
    class Log {
        
 	public:
        /*always initilized the logger in entrypoint
          if it's not initilize, GetCoreLogger() will return null*/
		static void Init();
        static void Shutdown();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() {
            
            if ( s_Logger == nullptr){
                std::cout <<"Logger is Null" <<std::endl;
            }
            return s_Logger;
        }

	private:
		static std::shared_ptr<spdlog::logger> s_Logger;

	};
};

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
	return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
	return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion)
{
	return os << glm::to_string(quaternion);
}


#define LOG_TRACE(...)	::Flare::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)	::Flare::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)	::Flare::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)	::Flare::Log::GetCoreLogger()->error(__VA_ARGS__)
