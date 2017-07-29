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

#ifndef _PEGASUS_UNIFORM_HPP_
#define _PEGASUS_UNIFORM_HPP_

//====================
// C++ includes
//====================
#include <string>                    // Passing uniform names.
#include <utility>                   // Forwarding variables passed into the templated method.

//====================
// Pegasus includes
//====================
#include <pegasus/graphics/gl.hpp>  // OpenGL API.

//====================
// Library includes
//====================
#include <glm/glm.hpp>              // Passing vectors and matrices to the shader.

namespace pegasus
{
	class Uniform final
	{
	private:
		//====================
		// Member variables
		//====================
		/** A reference to the ID of the shader program this uniform is attached to. */
		GLuint m_ID;

	private:
		//====================
		// Private methods
		//====================
		/**
		 * @brief Retrieves the location of the uniform within the shader.
		 *
		 * Each uniform within a shader is assigned a unique value, this
		 * method can be used to retrieve the location of the uniform within
		 * the shader.
		 *
		 * @param uniform    The name of the uniform within the shader.
		 *
		 * @returns          The location of the uniform within the shader.
		 */
		GLint getLocation(const std::string& name) const;

		/**
		 * @brief Sets the value of a uniform variable.
		 *
		 * This method is used to set a uniform variable to the value
		 * of an integer.
		 *
		 * @param location The location of the uniform within the shader.
		 * @param value    The integer value to send to the shader.
		 */
		void setParameter(GLint location, int value) const;

		/**
		 * @brief Sets the value of a uniform variable.
		 *
		 * This method is used to set a uniform variable to the value
		 * of a vec4 object.
		 *
		 * @param location The location of the uniform within the shader.
		 * @param vector   The vec4 values to send to the shader.
		 */
		void setParameter(GLint location, const glm::vec4& vector) const;

	public:
		//====================
		// Ctors and dtor
		//====================
		/**
		 * @brief Default constructor
		 * 
		 * The default constructor will set all of the member variables to
		 * default values.
		 */
		explicit Uniform();

		/**
		 * @brief Default destructor.
		 */
		~Uniform() = default;

		//====================
		// Getters and setters
		//====================
		/**
		 * @brief Sets the ID of the relevant shader program.
		 * 
		 * The ID is used to set and post the uniform variables to the shader
		 * program. The ID will be identical to the ID of the shader program
		 * that the uniform object has been instantiated within. This method should
		 * not be invoked outside the context of a shader program.
		 * 
		 * @param ID The ID of the shader program.
		 */
		void setID(GLuint ID);

		//====================
		// Methods
		//====================
		/**
		 * @brief Sends a variable as a uniform to the attached shaders.
		 *
		 * So communication can be achieved between C++ and glsl, uniform
		 * variables can be transferred to give shaders additional behavior. 
		 * This method makes use of forwarding of variables in order to support
		 * many different variable types.
		 *
		 * @param uniform   The name of the uniform in the glsl shader.
		 * @param value     The value to send to the shader.
		 */
		template <typename T>
		void set(const std::string& name, T value) const;
	};
	

	//====================
	// Methods
	//====================
	/**********************************************************/
	template <typename T>
	void Uniform::set(const std::string& name, T value) const
	{
		this->setParameter(this->getLocation(name), std::forward<T>(value));
	}

} // namespace pegasus

#endif//_PEGASUS_UNIFORM_HPP_