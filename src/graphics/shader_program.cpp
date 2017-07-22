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
#include <utility>  // Moving the shader to the shader program.

//====================
// Pegasus includes
//====================
#include <pegasus/graphics/shader_program.hpp>  // Class declaration.
#include <pegasus/utilities/logger_factory.hpp> // Logging messages to the external file.

namespace pegasus
{
	//====================
	// Static variables
	//====================
	ShaderProgram* ShaderProgram::m_pDefault = nullptr;

	//====================
	// Constant variables
	//====================
	const std::string DEFAULT_VERTEX_SHADER = 
		R"(#version 330 core
		layout (location = 0) in vec2 position;
		void main() {
			gl_Position = vec4(position, 0.0, 1.0);
		})";	

	const std::string DEFAULT_FRAGMENT_SHADER =
		R"(#version 330 core
		out vec4 colour;
		void main() {
			colour = vec4(1.0);
		})";

	//====================
	// Ctors and dtor
	//====================
	/**********************************************************/
	ShaderProgram::ShaderProgram()
		: Asset(), m_logger(LoggerFactory::getLogger("file.logger")), m_shaders(), m_uniform(), m_compiled(false)
	{
		m_ID = gl::createProgram();
		m_uniform.setID(m_ID);
	}

	/**********************************************************/
	ShaderProgram::~ShaderProgram()
	{
		gl::deleteProgram(m_ID);
	}

	//====================
	// Getters and setters
	//====================
	/**********************************************************/
	ShaderProgram* ShaderProgram::getDefault()
	{
		if (!m_pDefault)
		{
			m_pDefault = new ShaderProgram();
			// Create the vertex shader.
			Shader vs;
			vs.loadFromSource(gl::eShaderType::VERTEX, DEFAULT_VERTEX_SHADER);
			// Create the fragment shader.
			Shader fs;
			fs.loadFromSource(gl::eShaderType::FRAGMENT, DEFAULT_FRAGMENT_SHADER);
			// Attach the shaders.
			m_pDefault->attach(vs);
			m_pDefault->attach(fs);
			// Compile that bad boy.
			m_pDefault->compile();
		}

		return m_pDefault;
	}

	/**********************************************************/
	bool ShaderProgram::isCompiled() const
	{
		return m_compiled;
	}

	//====================
	// Methods
	//====================
	/**********************************************************/
	void ShaderProgram::attach(gl::eShaderType type, const std::string& filename)
	{
		Shader shader;
		if (shader.loadFromFile(type, filename))
		{
			m_shaders.push_back(shader);
		}
	}

	/**********************************************************/
	void ShaderProgram::attach(const Shader& shader)
	{
		m_shaders.push_back(std::move(shader));
	}

	/**********************************************************/
	void ShaderProgram::compile()
	{
		// Compile all of the shaders attached to this program.
		for (auto& shader : m_shaders)
		{
			// Only compile if it hasn't been already.
			if (!shader.isCompiled())
			{
				shader.compile();
			}
			// Attach the shader to the program.
			gl::attachShader(m_ID, shader.getID());
		}
		// Link the shaders and program together.
		gl::linkProgram(m_ID);
		// Retrieve the link state.
		GLint linked;
		glGetProgramiv(m_ID, GL_LINK_STATUS, &linked);
		// The program didn't link successfully, get the error log and log it.
		if (linked != GL_TRUE)
		{
			// Retrieve the length of the log.
			GLint logLength;
			glGetProgramiv(m_ID, GL_INFO_LOG_LENGTH, &logLength);
			// Populate the vector with the contents of the log.
			std::vector<GLchar> log(logLength);
			glGetProgramInfoLog(m_ID, logLength, &logLength, &log[0]);
			// Log the warning and delete the id.
			m_logger.warning("ShaderProgram:", m_name, "failed. Error:", &log[0]);
			m_shaders.clear();
			// Delete the program and set the compilation flag to false.
			gl::deleteProgram(m_ID);
			m_compiled = false;
		}
		// Unlink the shaders from the program.
		for (auto& shader : m_shaders)
		{
			glDetachShader(m_ID, shader.getID()); 
		}

		// It's succeeded, log an message and set the flag to true.
		m_logger.debug("ShaderProgram:", m_name, "linked successfully.");
		m_compiled = true;
		// Check for OpenGL errors.
		PEGASUS_GL_CHECK_ERRORS();
	}

	/**********************************************************/
	void ShaderProgram::process()
	{
		m_uniform.set("u_colour", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	}

	/**********************************************************/
	void ShaderProgram::bind(const ShaderProgram& program)
	{
		glUseProgram(program.getID());
	}

	/**********************************************************/
	void ShaderProgram::unbind()
	{
		glUseProgram(0);
	}

} // namespace pegasus