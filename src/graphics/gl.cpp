/*
* Pegasus Engine
* 2017 - Benjamin Carter (bencarterdev@outlook.com)
*
* This software is provided 'as-is', without any express or implied warranty.
* In no event will the authors be held liable for any damages arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it freely,
* subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented;
*    you must not claim that you wrote the original software.
*    If you use this software in a product, an acknowledgement
*    in the product documentation would be appreciated but is not required.
*
* 2. Altered source versions must be plainly marked as such,
*    and must not be misrepresented as being the original software.
*
* 3. This notice may not be removed or altered from any source distribution.
*/

//====================
// C++ includes
//====================
#include <string>

//====================
// Pegasus includes
//====================
#include <pegasus/graphics/gl.hpp>
#include <pegasus/utilities/logger.hpp>
#include <pegasus/utilities/logger_factory.hpp>

namespace pegasus
{
	namespace gl
	{
		//====================
		// Functions
		//====================
		/**********************************************************/
		GLenum initialize()
		{
			// Needed flag to get glew to work on linux/mac.
			glewExperimental = GL_TRUE;
			// Return the result of the initialization.
			return glewInit();
		}

		/**********************************************************/
		GLuint genBuffer()
		{
			GLuint buffer = 0;
			glGenBuffers(1, &buffer);

			return buffer;
		}

		/**********************************************************/
		void bindBuffer(eBufferType type, GLuint ID)
		{
			glBindBuffer(static_cast<GLenum>(type), ID);
		}

		/**********************************************************/
		void bufferData(eBufferType bufferType, std::size_t size, void* pData, eDrawType drawType)
		{
			glBufferData(static_cast<GLenum>(bufferType), size, pData, static_cast<GLenum>(drawType));
		}

		/**********************************************************/
		void enableVertexAttributeArray(GLint location)
		{
			glEnableVertexAttribArray(location);
		}

        /**********************************************************/
        GLuint createShader(eShaderType type)
        {
            return glCreateShader(static_cast<GLenum>(type));
        }

		/**********************************************************/
		void attachShader(GLuint programID, GLuint shaderID)
		{
			glAttachShader(programID, shaderID);
		}        

		/**********************************************************/
        GLint shaderStatus(GLuint ID)
        {
        	GLint status = 0;
        	glGetShaderiv(ID, GL_COMPILE_STATUS, &status);

        	return status;
        }

        /**********************************************************/
        void deleteShader(GLuint ID)
        {
        	if (ID)
        	{
        		glDeleteShader(ID);        		
        	}
        }

        /**********************************************************/
        GLuint createProgram()
        {
        	return glCreateProgram();
        }

        /**********************************************************/
        void deleteProgram(GLuint ID)
        {
        	if (ID)
        	{
        		glDeleteProgram(ID);        		
        	}
        }

        /**********************************************************/
        void linkProgram(GLuint ID)
        {
        	glLinkProgram(ID);
        }

        /**********************************************************/
        GLuint genTexture()
        {
        	// Generate the ID for the texture.
        	GLuint ID = 0;
        	glGenTextures(1, &ID);

        	return ID;
        }

        /**********************************************************/
        void bindTexture(eTextureType type, GLuint ID)
        {
        	glBindTexture(static_cast<GLenum>(type), ID);
        }

		/**********************************************************/
		void clearColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a)
		{
			glClearColor(r, g, b, a);
		}

		/**********************************************************/
		void clearColor(const glm::vec4& colour)
		{
			clearColor(colour.x, colour.y, colour.z, colour.w);
		}

		/**********************************************************/
		void clear()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		/**********************************************************/
		void enable(GLenum flag)
		{
			glEnable(flag);
		}

		/**********************************************************/
		void disable(GLenum flag)
		{
			glDisable(flag);
		}

		/**********************************************************/
		void checkErrors(const char* pFile, const char* pFunction, int line)
		{
			// Get the first error.
			GLenum error = glGetError();
			// Retain a static instance of the file logger.
			static Logger& log = LoggerFactory::getLogger("file.logger");
			// Loop through each error on the queue.
			while (error != GL_NO_ERROR)
			{
				// Store the current error message.
				std::string msg;
				// Find out which error type has occured.
				switch (error)
				{
				case GL_INVALID_OPERATION:
					msg = "Invalid operation";
					break;

				case GL_INVALID_ENUM:
					msg = "Invalid enumeration";
					break;

				case GL_INVALID_VALUE:
					msg = "Invalid value";
					break;

				case GL_OUT_OF_MEMORY:
					msg = "Invalid memory";
					break;

				case GL_INVALID_FRAMEBUFFER_OPERATION:
					msg = "Invalid frame-buffer operation";
					break;

				default:
					msg = "Invalid GL operation";
					break;
				}
				// Get the next error.
				error = glGetError();
				// Log the error to the external log file.
				log.error("OpenGL Error:", msg, "- file:", pFile, "- function: ", pFunction, "- line:", line);
			}
		}
	}

} // namespace pegasus
