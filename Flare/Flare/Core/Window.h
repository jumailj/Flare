#pragma once

#include <string>

namespace Flare {
    /* contain properties of window's title, width, height*/
    struct WindowProps{
        std::string Title;
        uint32_t Width;
        uint32_t Height;
        
        // windows props have default values;
        WindowProps(const std::string& title = "Flare", uint32_t width=1280, uint32_t height = 720) 
            :Title{title}, Width{width}, Height{height}
        {
        }
    };
    

    // Window interface
    class Window{
    public:

        virtual ~Window() {}
        
        virtual void OnUpdate() = 0;
        
        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;
        
        virtual void* GetNativeWindow() const = 0;
        
        static Window* Create(const WindowProps& props = WindowProps()); // here is the where the window is created. linux, windows, mac
    };
    
}