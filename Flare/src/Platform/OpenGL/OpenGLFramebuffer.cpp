#include "OpenGLFramebuffer.h"
#include <Flare/Core/Log.h>

#include<glad/glad.h>

namespace Flare{

    OpenGLFrameBuffer::OpenGLFrameBuffer(const FramebufferSpecification& spec)
    :m_Specification(spec)
    {
        Invalidate();
    }


    OpenGLFrameBuffer::~OpenGLFrameBuffer() 
    {
        glCreateFramebuffers(0,&m_RendererID);
    }

    void OpenGLFrameBuffer::Invalidate()
     {
        glCreateFramebuffers(1,&m_RendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

        glCreateTextures(GL_TEXTURE_2D,1,&m_ColorAttachment);
        glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Specification.Widht, m_Specification.Height, 0,GL_RGBA, GL_UNSIGNED_BYTE, nullptr); 

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

        //DEPTH BUFFER;
        glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment);
        glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);

        // USE ON OF THESE TWO.AT A TIME
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Specification.Widht, m_Specification.Height);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Specification.Widht, m_Specification.Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
    
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);
        
        if ( glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            LOG_ERROR("FRAMEBUFFER IS IMCOMPLETED!");
        }


        glBindFramebuffer(GL_FRAMEBUFFER, 0);

     }


    void OpenGLFrameBuffer::Bind() 
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
    }
    void OpenGLFrameBuffer::Unbind() 
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }



}