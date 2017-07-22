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
#include <pegasus/graphics/uniform.hpp> // Class declaration.

namespace pegasus
{
	//====================
	// Ctors and dtor
	//====================
	/**********************************************************/
	Uniform::Uniform()
		: m_ID(0)
	{
		// Empty.
	}

	//====================
	// Getters and setters
	//====================
	/**********************************************************/
	void Uniform::setID(GLuint ID)
	{
		m_ID = ID;
	}

	//====================
	// Private methods
	//====================
	/**********************************************************/
	GLint Uniform::getLocation(const std::string& name) const
	{
		return glGetUniformLocation(m_ID, name.c_str());
	}

	//====================
	// Methods
	//====================
	/**********************************************************/
	void Uniform::setParameter(GLint location, const glm::vec4& vector) const
	{
		glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
	}

} // namespace pegasus 