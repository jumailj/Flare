#include "OpenGLTexture.h"
#include <Flare/Core/Log.h>

#include <stb_image.h>
#include <glad/glad.h>

#include <fstream>


namespace Flare{

    bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good(); // Returns true if the file exists and is readable
    }

    /*generate texture with width and height*/
    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height) 
        :m_Width(width), m_Height(height)
    {
        m_InternalFormat = GL_RGBA8;
        m_DataFormat = GL_RGBA;

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINE);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

    }


    /* load texture from path */
    OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
       :m_Path(path)    
    {
        int widht, height, channels;
        
        /*
          in computer graphics the orgin (0,0) is typically located at the bottom left corner of an image.
          Which is differnt from the top left corner of an image. This can lead to a siguation where an 
          image apperas upside down when loaded in. stbi_set_flip_vertically_load(true), will flip the 
          image vertically so that the origin is at the top left corner.
        */
		stbi_set_flip_vertically_on_load(1);


		stbi_uc* data =  stbi_load(path.c_str(),&widht, &height, &channels, 0 );
		if(!data) {
           std::string errMsg = stbi_failure_reason();
            LOG_ERROR("image not loaded! Reason:{errmsg}");
             // std::cerr << "Error loading image: " << stbi_failure_reason() << std::endl;
        }

		m_Width = widht;
		m_Height = height;

        GLenum internalFormat = 0, dataFormat = 0;
        //we have two channels in image, RGB and RBG with Alpha.
		if (channels == 4) {
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3) {
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

        // setting internals
        m_InternalFormat = internalFormat;
        m_DataFormat = dataFormat;


		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		// glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data); // dealocate
    }

    void OpenGLTexture2D::SetData(void *data, uint32_t size)
    {
        uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;

        if(size != m_Width* m_Height * bpp) {  LOG_ERROR("data must be entire texture!");}

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
    }

    void OpenGLTexture2D::Bind(uint32_t slot ) const
    {
        glBindTextureUnit(slot,m_RendererID);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_RendererID);
    }

}