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
// Pegasus includes
//====================
#include <pegasus/graphics/buffer_description.hpp> // Contains information regarding describing a buffer.

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
