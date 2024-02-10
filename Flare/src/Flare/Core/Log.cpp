#include "Log.h"

namespace Flare{
    
    // don't need to use Ref.
     std::shared_ptr<spdlog::logger> Log::s_Logger;
    
    void Log::Init(){
        spdlog::set_pattern("%^[%T] %n: %v%$");
        s_Logger = spdlog::stdout_color_mt("Flare");
        s_Logger->set_level(spdlog::level::trace);
    }
    
};