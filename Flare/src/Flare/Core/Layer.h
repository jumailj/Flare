#pragma once 

#include <Flare/Core/Timestep.h>
#include "Core.h"
#include <Flare/Events/Event.h>

namespace Flare{
    
    class Layer{
    public:
        
        Layer(const std::string& name = "Layer");
        
        virtual ~Layer();
        
        virtual void OnAttach(){}
        virtual void OnDetach(){}
        virtual void OnUpdate(Timestep ts) {}
        virtual void OnImGuiRender() {}
        virtual void OnEvent(Event& event){}
        
        inline const std::string& GetName() const {return m_DebugName;}
        
    protected:
        std::string m_DebugName; // for debug
    };
    
}