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
#include <vector> // Stores the error log of the shader.

//====================
// Pegasus includes
//====================
#include <pegasus/graphics/shader.hpp>           // Class declaration.
#include <pegasus/utilities/file_reader.hpp>     // Loading the glsl source file from a directory.
#include <pegasus/utilities/logger_factory.hpp>  // Loading a logging object.

namespace pegasus
{
	//====================
	// Ctors and dtor
	//====================
	/**********************************************************/
	Shader::Shader()
		: Asset(), m_logger(LoggerFactory::getLogger("file.logger")), m_source(), m_type(), m_compiled(false)
	{
		// Empty.
	}

	/**********************************************************/
	Shader::~Shader()
	{
		gl::deleteShader(m_ID);
	}

	//====================
	// Getters and setters
	//====================
	/**********************************************************/
	bool Shader::isCompiled() const
	{
		return m_compiled;
	}

	//====================
	// Methods
	//====================
	/**********************************************************/
	bool Shader::loadFromFile(gl::eShaderType type, const std::string& filename)
	{
		// TODO(Ben): Check for file extension.
		// Create the reader and open the file.
		FileReader reader(filename);
		// Check that the file opened successfully, if not log a warning.
		if (reader.failed())
		{
			m_logger.warning("Failed to load shader file:", filename);
			return false;
		}
		// Store the source of the shader.
		m_source = reader.getSource();
		m_type = type;
		// The file loaded successfully.
		return true;
	}

	/**********************************************************/
	void Shader::loadFromSource(gl::eShaderType type, const std::string& source)
	{
		m_source = source;
		m_type = type;
	}

	/**********************************************************/
	void Shader::compile()
	{
		// Generate the ID for the shader.
		m_ID = gl::createShader(m_type);
		// Get the source of the shader and set it for the shader ID.
		const GLchar* pSource = m_source.c_str();
		glShaderSource(m_ID, 1, (const GLchar**)&pSource, nullptr);
		// Compile the shader.
		glCompileShader(m_ID);
		// Check the results of the compilation and log any errors.
		GLint status = gl::shaderStatus(m_ID);
		// Check if the shader compiled successfully.
		if (status != GL_TRUE)
		{
			// It didn't succeed, log the reason.
			GLint logSize = 0;
			glGetShaderiv(m_ID, GL_INFO_LOG_LENGTH, &logSize);
			// Get the contents of the log.
			std::vector<GLchar> log(logSize);
			glGetShaderInfoLog(m_ID, logSize, &logSize, &log[0]);
			// Delete the shader as it failed to compile.
			gl::deleteShader(m_ID);
			// Log the issue.
			m_logger.warning("Shader", m_name, "failed to compile:", &log[0]);
		}
		else
		{
			// The shader compiled successfully.
			m_compiled = true;
		}
		// Success!
		m_logger.debug("Shader", m_name, "compiled successfully");
		// Clear the shader source.
		m_source.clear();
		// Check for any gl problems.
		PEGASUS_GL_CHECK_ERRORS();
	}

} // namespace pegasus