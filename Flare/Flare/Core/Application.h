#pragma once

#include <string>  //later change it to precompiled header.

namespace Flare {
    
    class Application 
    {
        public:
            Application(const std::string &name = "Flare");
            virtual ~Application();
            
            void Run();
            void Close();
            
        private:
            bool m_Running = true;
        
    };

}