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

#ifndef _PEGASUS_SHADER_HPP_
#define _PEGASUS_SHADER_HPP_

//====================
// Pegasus includes
//====================
#include <pegasus/core/asset.hpp>   // Shader is a type of asset/resource.
#include <pegasus/graphics/gl.hpp>  // Using abstracted openGL functions.

namespace pegasus
{
	//====================
	// Forward declarations
	//====================
	class Logger;

    class Shader final : public Asset
    {
    private:
    	/** Used to log warnings and debug messages. */
    	Logger&         m_logger;
    	/** The source of the shader to compile. */
    	std::string     m_source;
    	/** The type of shader being registered. */
    	gl::eShaderType m_type;
    	/** Whether the shader has been compiled. */
    	bool            m_compiled;

    public:
    	//====================
    	// Ctors and dtor
    	//====================
    	/**
    	 * @brief Default constructor for the Shader.
    	 * 
    	 * The default constructor will set all of the member variables
    	 * to default values. The shader is not useable in this state, and additional
    	 * call to loadFromFile and compile must be made before the shader can be used
    	 * for rendering.
    	 */
        explicit Shader();

        /**
         * @brief Destructor for the shader.
         * 
         * When the shader is destroyed, it will delete the retained shader ID if one
         * has been created by the graphics API.
         */
        ~Shader();

        //====================
        // Getters and setters
        //====================
        /**
         * @brief Retrieve the compilation state of the shader.
         * 
         * The compilation flag states whether the shader has compiled successfully, 
         * it will only be set if the shader was compiled without any warnings or errors.
         * 
         * @returns The compilation state of the shader.
         */
        bool isCompiled() const;
        
        //====================
        // Methods
        //====================
        /**
         * @brief Loads a shader from a specified file directory.
         * 
         * When this method is invoked, it will create a file reader and load in the contents
         * of the specified file. If the file does not exist or was unable to open, a message 
         * will be logged to the external log file. If the file opened successfully, the source
         * of the file is stored until the shader is compiled.
         * 
         * @param type The type of shader to create.
         * @param filename The file directory of the shader to load.
         * 
         * @returns True if the file loads successfully from the specified directory.
         */
        bool loadFromFile(gl::eShaderType type, const std::string& filename);

        /**
         * @brief Loads a shader with the specified inline source.
         * 
         * When this method is invoked, it will set the source of the shader to the inline source
         * passed in as the source argument. All error checking for incorrect source wil be found
         * during compilation.      
         * 
         * @param type The type of shader to create.
         * @param source The inline glsl source.
         */
        void loadFromSource(gl::eShaderType type, const std::string& source);

        /**
         * @brief Compiles the shader source file.
         * 
         * When this method is invoked, the graphics API will attempt to parse and compile the
         * external shader file. If the shader failed to compile, a warning is logged (with the specified
         * reason for failure) and the compilation state is set to false. The source is cleared after compilation
         * is attempted.
         */
        void compile();
    };

} // namespace pegasus

#endif//_PEGASUS_SHADER_HPP_
