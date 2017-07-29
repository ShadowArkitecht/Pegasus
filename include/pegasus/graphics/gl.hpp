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

#ifndef _PEGASUS_GL_HPP_
#define _PEGASUS_GL_HPP_

//====================
// Library includes
//====================
#include <GL/glew.h>    // OpenGL functions.
#include <glm/glm.hpp>  // Mathematic functions.

namespace pegasus
{
	namespace gl
	{
        //====================
        // Enumerations
        //====================
        enum class eBufferType
        {
            /** A buffer that will be constructed as a vertex buffer. */
            VERTEX = GL_ARRAY_BUFFER
        };

        enum class eDrawType
        {
            /** The vertices will be drawn as static (the data will not change). */
            STATIC = GL_STATIC_DRAW,
            /** The vertices will be drawn as dynamic (data is likely to change i.e. sprite batch. */
            DYNAMIC = GL_DYNAMIC_DRAW
        };

        enum class eShaderType
        {
            /** The shader created will be a vertex shader. */
            VERTEX = GL_VERTEX_SHADER,
            /** The shader created will be a pixel/fragment shader. */
            FRAGMENT = GL_FRAGMENT_SHADER
        };

		enum class eTextureType
		{
			/** The texture type of the image. */
			TEXTURE_2D = GL_TEXTURE_2D
		};

		enum class eFilterType
		{
			/** The pixels of the texture will be applied with neighbouring pixels in mind. */
			NEAREST = GL_NEAREST,
			/** The pixels of the textures will be applied linearly. */
			LINEAR = GL_LINEAR
		};

		enum class eWrapType
		{
			/** The image will be clamped to the rendering buffer. */
			CLAMP = GL_CLAMP,
			/** The image will repeat (without stretching) across the rendering buffer. */
			REPEAT = GL_REPEAT
		};

		//====================
		// Functions
		//====================
		/**
		 * @brief Initializes the GLEW library for use.
		 *
		 * Before the GLEW library can be used, it must be initialized. The initalization
		 * must occur after the GL context has been established. An error code is returned by
		 * the initialization function, if it does not equal GLEW_OK, an exception will be thrown
		 * by the Window class.
		 *
		 * @returns The resulting code of the initialization.
		 */
		GLenum initialize();

		/**
		 * @brief Generates a buffer for use.
		 *
		 * A buffer is a just a simple integer value that is used to bind different behavior
		 * within OpenGL, such as textures or vertex buffers.
		 *
		 * @returns An integer representing a generated buffer.
		 */
		GLuint genBuffer();

		/**
		 * @brief Binds the specified buffer with its type and ID.
		 *
		 * When the buffer is bound, it will bind a specific type depending on the
		 * buffer type specified. The ID refers to the unique ID assigned all buffers,
		 * and textures, which will use their behavior when bound.
		 *
		 * @param type The type of buffer to bind.
		 * @param ID   The unique ID of the buffer.
		 */
		void bindBuffer(eBufferType type, GLuint ID);

		/**
		 * @brief Populates a buffer with the specified information.
		 *
		 * So that the buffer knows what information it is to utilise when bound,
		 * specific information is given to bind certain information, which will be used
		 * when the buffer is re-bound. This function is predominantly used in conjunction with
		 * the BufferDescription to provide an abstracted solution to the OpenGL library.
		 *
		 * @param bufferType The type of buffer to generate.
		 * @param size       The total size of memory to be used (in bytes).
		 * @param pData      The raw data to bind.
		 * @param drawType   How the buffer will be used and drawn.
		 */
		void bufferData(eBufferType bufferType, std::size_t size, void* pData, eDrawType drawType);

		/**
		* @brief Enables a vertex attribute array, for communication with shaders.
		*
		* Vertex atrribute arrays are for enabling contact between the vertices of a mesh, and glsl
		* shaders. For each attribute assigned, it will have a mirrored variable as a location variable
		* within the vertex shader. By default the attributes enabled are for vertex position and uv-coordinates.
		* 
		* @param location The location of the vertex attribute array to activate.
		*/
		void enableVertexAttributeArray(GLint location);

        /**
         * @brief Creates a new shader ID.
         *
         * When a shader is compiled within the application, it will create a buffer that will be used
         * to bind the shader and contain all of its functionality.
         *
         * @param type The type of shader to generate.
         *
         * @returns The generated ID of the new shader object.
         */
        GLuint createShader(eShaderType type);

        /**
         * @brief Attaches a shader to the specified program.
         * 
         * When the shader is attached to a program, when the shader is bound and objects
         * rendered, it will use the rendering behavior defined within the glsl files.
         * 
         * @param programID The program to attach the shader to.
         * @param shaderID The shader to attach.
         */
        void attachShader(GLuint programID, GLuint shaderID);

        /**
         * @brief Deletes the specified shader from the cpu.
         * 
         * This method is used to remove the shader data from the GPU with the specified ID. This method
         * is invoked when a shader is no longer used or failed to compile successfully.
         * 
         * @param ID The ID of the shader to delete.
         */
        void deleteShader(GLuint ID);

        /**
         * @brief Retrieves the compilation status of the specified shader.
         * 
         * When a shader has been compiled, this function can be used to check the compilation status,
         * a problem would have occured if the value returned is not equal to GL_TRUE.
         * 
         * @param ID The ID of the shader to check.
         * 
         * @returns the compilation state of the specified shader.
         */
        GLint shaderStatus(GLuint ID);

        /**
         * @brief Create the program and returns the unique ID.
         * 
         * A program is responsible for the linking of different vertex and fragment shaders together,
         * which when bound to the context will alter the rendering of any currently bound vertex/array
         * buffers.
         * 
         * @returns The unique ID of the new program.
         */
        GLuint createProgram();

        /**
         * @brief Delete the program and frees the memory on the GPU.
         * 
         * The program is deleted when a shader program is no longer referenced and the threshold of 
         * memory is reached, it is invoked within the objects constructor.
         * 
         * @param ID The id of the program to delete.
         */
        void deleteProgram(GLuint ID);

        /**
         * @brief Links the program and its attached shaders together.
         * 
         * When the program is linked, it will link all of the attached shaders and retain their
         * rendering behavior within the program ID. The shaders can be detached once they are linked
         * to the program.
         * 
         * @param ID The id of the program to link.
         */
        void linkProgram(GLuint ID);

        /**
         * @brief Generates an ID for a texture object.
         * 
         * This method is invoked within the Texture object to create a unique ID for the texture,
         * which when bound will render the texture on the currently bound context.
         * 
         * @returns The ID of the generated texture.
         */
        GLuint genTexture();

        /**
         * @brief Binds the texture to the rendering context.
         * 
         * When the texture is bound, if it is utilized by the currently bound shader, it will use
         * the texture and apply it to any rendering meshes that will utilise this behavior.
         * 
         * @param type The type of texture bound.
         * @param ID The ID of the texture to bind. 
         */
        void bindTexture(eTextureType type, GLuint ID);

		/**
		 * @brief Clears the buffer to the specified colour.
		 *
		 * This is used to reset the buffer to the specified colour each frame. It should be
		 * noted that the values provided will be clamped to between 0 and 1.
		 *
		 * @param r The red intensity.
		 * @param g The green intensity.
		 * @param b The blue intensity.
		 * @param a The alpha intensity.
		 */
		void clearColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a);

		/**
		 * @brief Clears the buffer to the specified colour.
		 *
		 * This is used to reset the buffer to the specified colour each frame. It should be
		 * noted that the values provided will be clamped to between 0 and 1.
		 *
		 * @param colour The colour to set the cleared color to.
		 */
		void clearColor(const glm::vec4& colour);

		/**
		 * @brief Clears the color and depth buffer bits.
		 *
		 * This function is called at beginning of each render frame to reset
		 * the image to a default value and prevent artifacting.
		 *
		 */
		void clear();

		/**
		 * @brief Enables the specified Gl flag.
		 *
		 * @param flag The GL enumeration to enable.
		 */
		void enable(GLenum flag);

		/**
		 * @brief Disables the specified Gl flag.
		 *
		 * @param flag The GL enumeration to disable.
		 */
		void disable(GLenum flag);

		/**
		 * @brief Checks for any errors that may occured during any OpenGL calls.
		 *
		 * After a series of OpenGL calls are made, this error checker is invoked to ensure
		 * that no incorrect values or states were passed to openGL. If any errors occured,
		 * they are logged to the external file log. This method is not invoked implicitly, rather
		 * the Gl_PEGASUS_CHECK_ERRORS() macro is invoked to also provide a file and line number.
		 *
		 * @param pFile     The file the error occured within.
		 * @param pFunction The name of the function where the error occured.
		 * @param line      The line that the incorrect state to passed to.
		 */
		void checkErrors(const char* pFile, const char* pFunction, int line);


	} // namespace gl

} // namespace pegasus

//====================
// Macros
//====================
#define PEGASUS_GL_CHECK_ERRORS() pegasus::gl::checkErrors(__FILE__, __func__, __LINE__)

#endif//_PEGASUS_GL_HPP_
