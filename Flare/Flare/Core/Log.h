#pragma once

#include <memory>
#include <iostream>

#include "../../vendor/spdlog/include/spdlog/spdlog.h" // for codelite;
#include "../../vendor/spdlog/include/spdlog/sinks/stdout_color_sinks.h" // for codelite;


namespace Flare{
    
    class Log {
        
 	public:
        /*always initilized the logger in entrypoint
          if it's not initilize, GetCoreLogger() will return null*/
		static void Init();

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

#define LOG_TRACE(...)	::Flare::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)	::Flare::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)	::Flare::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)	::Flare::Log::GetCoreLogger()->error(__VA_ARGS__)
