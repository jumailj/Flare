#pragma once

#include <Flare/Renderer/GraphicContext.h>

struct GLFWwindow;

namespace Flare{

    class OpenGLContext : public GraphicContext {
    public:

        OpenGLContext(struct GLFWwindow * windowHandle);

        virtual void Init() override;
        virtual void SwapBuffers() override;

        private:
        
        GLFWwindow* m_WindowHandle;

    };
}