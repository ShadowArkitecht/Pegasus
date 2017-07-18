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
// Pegasus includes
//====================
#include <pegasus/graphics/buffer.hpp> // Class declaration.
#include <pegasus/graphics/gl.hpp>     // OpenGL encapsulated functions.

namespace pegasus
{
	//====================
	// Ctors and dtor
	//====================
	/**********************************************************/
	Buffer::Buffer()
		: m_ID(0), m_type()
	{
		// Empty.
	}

	/**********************************************************/
	Buffer::Buffer(const BufferDescription& description)
		: m_ID(0), m_type(description.bufferType)
	{
		// Generate the unique ID for the buffer.
		m_ID = gl::genBuffer();
		// Bind the buffer to define its behavior.
		Buffer::bind(*this);
		// Populate the buffer with specific information.
		gl::bufferData(description.bufferType, description.stride * description.size, description.pData, description.drawType);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
		glEnableVertexAttribArray(0);
		// Unbind the buffer to set the state back to normal.
		Buffer::unbind(*this);
		// Check for errors.
		PEGASUS_GL_CHECK_ERRORS();
	}

	/**********************************************************/
	Buffer::~Buffer()
	{
		if (m_ID)
		{
			glDeleteBuffers(1, &m_ID);
			m_ID = 0;
		}
	}

	//====================
	// Getters and setters
	//====================
	/**********************************************************/
	GLuint Buffer::getID() const
	{
		return m_ID;
	}

	/**********************************************************/
	eBufferType Buffer::getType() const
	{
		return m_type;
	}

	//====================
	// Methods
	//====================
	/**********************************************************/
	void Buffer::bind(const Buffer& buffer)
	{
		gl::bindBuffer(buffer.getType(), buffer.getID());
	}

	/**********************************************************/
	void Buffer::unbind(const Buffer& buffer)
	{
		gl::bindBuffer(buffer.getType(), 0);
	}

} // namespace pegasus
