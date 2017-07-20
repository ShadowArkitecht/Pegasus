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

#ifndef _PEGASUS_SHADER_PROGRAM_HPP_
#define _PEGASUS_SHADER_PROGRAM_HPP_

//====================
// C++ includes
//====================
#include <vector> // Storing a list of shaders attached to this program.

//====================
// Pegasus includes
//====================
#include <pegasus/core/asset.hpp>      // shader program is a type of retained asset.
#include <pegasus/graphics/shader.hpp> // Storing different shader objects.

namespace pegasus
{
	//====================
	// Forward declarations
	//====================
	class Logger;

	class ShaderProgram final : public Asset
	{
	private:
		//====================
		// Member variables
		//====================
		/** Logging warnings and errors to the external file. */
		Logger&             m_logger;
		/** A list of all shaders attached to this program. */
		std::vector<Shader> m_shaders;
		/** The compilation flag for the compiling and linking of shaders. */
		bool                m_compiled;

	public:
		//====================
		// Ctors and dtor
		//====================
		/**
		 * @brief Default constructor for the shader program.
		 * 
		 * The default constructor will set all of the member variables
		 * to default values. The shader program will not render any behavior
		 * in this state, shaders must be attached and the program must be compiled.
		 */
		explicit ShaderProgram();

		/**
		 * @brief Destructor for the shader program.
		 * 
		 * The destructor will destroy the retained program ID and free the memory
		 * for additional use.
		 */
		~ShaderProgram();

		//====================
		// Getters and setters
		//====================
		/**
		 * @brief Retrieves the compilation state of the shader program.
		 * 
		 * The compilation flag states the the progress of the shader program.
		 * The compilation is always false if compile has not been called or failed
		 * to compile the linked shaders.
		 * 
		 * @returns The compilation flag of the shader program.
		 */
		bool isCompiled() const;

		//====================
		// Methods
		//====================
		/**
		 * @brief Attaches the shader at the specified file directory.
		 * 
		 * When a shader is attached in this manner, it is loaded from the specified
		 * directory. The shader is only attached to the program if it was loaded without
		 * any errors. The shader is not compiled during this process, an additional call
		 * to ShaderProgram::compile must be made.
		 * 
		 * @param type     The type of shader to attach.
		 * @param filename The directory to load the shader from.
		 */
		void attach(gl::eShaderType type, const std::string& filename);

		/**
		 * @brief Attaches the shader object to the program.
		 * 
		 * When the shader is attached in this manner, the shader object is moved into the
		 * program, which will now control its life-time. The shader object will be unuseable
		 * outside the scope of this class.
		 *
		 * @param shader The shader object to attach to the program.  
		 */
		void attach(const Shader& shader);

		/** @brief Compiles the shader object, ready for use.
		 *
		 * This method abstracts the behavior from the Shader objects
		 * and invokes the subsequent objects compile method. The ShaderProgram
		 * will only compile if it not already been compiled.
		 */
		void compile();

		/** @brief Processes the uniforms attached to the shader.
		 *
		 * When this method is invoked, it will update all of the subsequent
		 * uniform variables contained within the external shaders and change their
		 * values. This will also invoke the on_update function contained within the 
		 * attached shaders, which is used to update uniform variables without re-compilation.
		 */
		void process();

		/** @brief Binds the program to the current context and utilises its behavior.
		 *
		 * When a shader program is bound, any object that is subsequently rendered
		 * will utilise the behavior defined in the external glsl shaders.
		 *
		 * @param program The shader program to bind to the context.
		 */
		static void bind(const ShaderProgram& program);

		/* @brief Unbinds the shader program object.
		 *
		 * When the shader program is unbound, any objects that render after this
		 * statement will not utilise the behavior defined in the glsl shaders.
		 */
		static void unbind();
	};

} // namespace pegasus

#endif//_PEGASUS_SHADER_PROGRAM_HPP_