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

#ifndef _PEGASUS_BUFFER_HPP_
#define _PEGASUS_BUFFER_HPP_

//====================
// Pegasus includes
//====================
#include <pegasus/graphics/buffer_description.hpp> // Contains the definitions for buffer initialization.

namespace pegasus
{
	class Buffer final
	{
	private:
		//====================
		// Member variables
		//====================
		/** The unique ID of the buffer. */
		GLuint          m_ID;
		/** The type of buffer that has been created. */
		gl::eBufferType m_type;

	public:
		//====================
		// Ctors and dtor
		//====================
		/**
		 * @brief Default constructor for the Buffer.
		 * 
		 * The default constructor will set all of the member variables
		 * to default values. The buffer will not render in this state, the constructor
		 * that takes in a BufferDescription should be used to define the behavior
		 * of this buffer.
		 */
		explicit Buffer();

		/**
		 * @brief Constructor that will populate a useable buffer.
		 * 
		 * When this constructor is invoked, it will use the information defined
		 * within the buffer description to generate a buffer. The buffer can then
		 * be subsequently bound and re-used externally and retain the behavior that 
		 * was described. 
		 * 
		 * @param description [description]
		 */
		explicit Buffer(const BufferDescription& description);

		/**
		 * @brief Destructor for the Buffer.
		 * 
		 * The destructor will de-allocate the buffer ID that is being retained by 
		 * this instance.
		 */
		~Buffer();

		//====================
		// Getters and setters
		//====================
		/**
		 * @brief Retrieves the ID of the buffer.
		 * 
		 * The ID is unique to each buffer within the application. The ID contains
		 * all the information that was described when the buffer was instantiated. 
		 * If the buffer has been destroyed or initialization was not successful, the value
		 * will be equal to one.
		 * 
		 * @returns The ID of the buffer.
		 */
		GLuint getID() const;

		/**
		 * @brief Retrieves the type of the buffer created.
		 * 
		 * The type refers to the behavior of the buffer itself, each type contains slightly
		 * different information. The most commonly used is the vertex buffer, which is primarily
		 * used for rendering.
		 * 
		 * @returns The type of buffer.
		 */
		gl::eBufferType getType() const;

		//====================
		// Methods
		//====================
		/**
		 * @brief Binds the specified buffer as the current context.
		 * 
		 * In order to use the information supplied to the buffer, it must be bound
		 * as the current context. Once the buffer has been bound, it can be used to 
		 * draw the information described upon object initialization. If the object is not
		 * bound before behavior is needed, it may result in undefined behavior.
		 * 
		 * @param buffer The buffer to bind to the context.
		 */
		static void bind(const Buffer& buffer);

		/**
		 * @brief Unbinds the specified buffer.
		 * 
		 * To set the rendering state back to a default state, the buffer must be unbound
		 * when its use is no longer needed. if objects are not unbound, it may result in undefined
		 * graphical issues.
		 * 
		 * @param buffer The buffer to unbind.
		 */
		static void unbind(const Buffer& buffer);
	};

} // namespace pegasus

#endif//_PEGASUS_BUFFER_HPP_
