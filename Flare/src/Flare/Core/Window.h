#pragma once

#include <sstream>
#include <Flare/Events/Event.h>


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
    
    // Window interface, abstract class.
    class Window{
    public:
    
        using EventCallbackFn = std::function<void(Event&)>; //::Flare::

        virtual ~Window() {
            //before delete the parent object, this should be destruct.
        }
        
        virtual void OnUpdate() = 0;
        
        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;
        
        virtual void Init(const WindowProps& props) = 0;
        virtual void Shutdown() = 0;
        
        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
        
        virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;
        virtual void* GetNativeWindow() const = 0;  
        
        static Window* Create(const WindowProps& props = WindowProps()); // where windows is created. linux, windows, mac
    };
    
}