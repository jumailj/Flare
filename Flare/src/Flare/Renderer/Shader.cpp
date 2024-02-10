#include "Shader.h"

#include <vector>

#include <glad/glad.h>
#include <Flare/Core/Log.h>
#include <glm/gtc/type_ptr.hpp>


namespace Flare{

    Shader::Shader(const std::string &vertexSrc, const std::string &fragmentSrc){

        GLint isCompiled = 0;// for vertex and fragment;

        //1.VERTEX

        // create an empty vertex shader handle, in gpu
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

        //send the vertex shader source code to GL
        const GLchar *source = vertexSrc.c_str(); //null char terminated.
        glShaderSource(vertexShader, 1, &source,0);

        //compile the vertex shader
        glCompileShader(vertexShader);

        //check fo any compiliation errors.
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if(isCompiled == GL_FALSE) 
        {
            GLint maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

            // the maxlenght includes the NULl character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertexShader,maxLength,&maxLength,&infoLog[0]);

            // we don't need the shader anymore.
            glDeleteShader(vertexShader);
            // use the infolog as you see fit.
            LOG_ERROR("[VERTEX SHADER] compilation failure");
            LOG_ERROR("{0}", infoLog.data());

            // no error handling..
            return;
        }   

        //2. FRAGMENT
        // create an empty fragment shader handle
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        //send the fragment shader source code to GL
        source = (const GLchar*) fragmentSrc.c_str();
        glShaderSource(fragmentShader, 1, &source, 0);

        //compile the fragment shader 
        glCompileShader(fragmentShader);

        // check for any compiliation errors.
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if(isCompiled == GL_FALSE){
            GLint maxLength = 0;
            glGetShaderiv(fragmentShader,GL_INFO_LOG_LENGTH, &maxLength);

            // the maxlenght includes the NULl character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

            // we don't need the shader anymore.
            glDeleteShader(fragmentShader);
            glDeleteShader(vertexShader); // if fragmentshader get error then don't need vertex

            LOG_ERROR("compilation failure");
            LOG_ERROR("{0}", infoLog.data());
            
            //no error handling..
            return;
        }

        //3. LINKING
        // vertex and fragment shaders are successfully compiled.
        // now time to link together into a program.
        
        // get a program object.
        m_RendererID = glCreateProgram();
        GLuint program = m_RendererID;

        // attach our shaders to our program
        glAttachShader(program,vertexShader);
        glAttachShader(program,fragmentShader);

        //link our program
        glLinkProgram(program);

        //check if program get linked.
        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
        
        if(isLinked == GL_FALSE){

            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            //the maxlength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            // we don't need th program anymore
            glDeleteProgram(program);

            //don't leak shader either.
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            LOG_ERROR("Shader Linking Failure");
            LOG_ERROR("{0}", infoLog.data());

            return;
        }

        //always detach shaders after a successful link
        glDetachShader(program, vertexShader);
        glDetachShader(program, fragmentShader);  
    }

    Shader::~Shader() {
        glDeleteProgram(m_RendererID);
    }

    void Shader::Bind() const 
    {
        glUseProgram(m_RendererID);
    }

    void Shader::Unbind() const 
    {
        glUseProgram(0);
    }

    void Shader::UploadUniformFloat4(const std::string name, const glm::vec4& value)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform4f(location,value.x, value.y, value.z, value.w);

    }

    void Shader::UploadUniformMat4(const std::string name, const glm::mat4& matrix)
	{
		GLint location =  glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}



}