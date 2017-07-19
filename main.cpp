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
#include <cstdlib>   // Macros for exit failure or success.
#include <stdexcept> // Catching any runtime_error exceptions being thrown.
#include <array>     // An array of vertices.

//====================
// Pegasus includes
//====================
#include <pegasus/utilities/logger.hpp>          // Creating different logging objects.
#include <pegasus/utilities/console_policy.hpp>  // Registering the console policy with a logger.
#include <pegasus/utilities/file_policy.hpp>     // Registering the file policy with a logger.
#include <pegasus/utilities/logger_factory.hpp>  // Storing and retrieval of different logs.
#include <pegasus/core/config_file.hpp>          // Loading the external configuration file.
#include <pegasus/utilities/xml_serializable_service.hpp> // Registering the xml serializable service with a factory.
#include <pegasus/utilities/lua_serializable_service.hpp> // Registering the lua serializable service with a factory.
#include <pegasus/core/resources.hpp> // Loading and storing the Resources.xxx file.
#include <pegasus/utilities/exceptions/no_resource_exception.hpp> // Caught if the Resources.xxx file fails to load.
#include <pegasus/core/window.hpp>              // Creating an sdl window.
#include <pegasus/graphics/buffer.hpp>          // Generating a vertex buffer.
#include <pegasus/graphics/vertex.hpp>          // Setting the vertices of the mesh.
#include <pegasus/graphics/shader_program.hpp>  // Creating a shader program and linking glsl files.

using namespace pegasus;

//====================
// Functions
//====================
int main(int argc, char** argv)
{
	// Create a logger object that will print messages to the console.
	auto cl = std::make_unique<Logger>(std::make_unique<ConsolePolicy>());
	// Create a logger object that will send messages to an external file.
	auto fl = std::make_unique<Logger>(std::make_unique<FilePolicy>("log.txt"));
	// Register the console logger with the factory.
	LoggerFactory::registerLogger("console.logger", std::move(cl));
	LoggerFactory::registerLogger("file.logger", std::move(fl));

	// Create a configuration file object.
	ConfigFile config;
	try
	{
		// Attempt to open and parse the configuration file.
		config.open("config.pegasus");
	}
	catch (std::runtime_error& e)
	{
		// Log that the config file failed to open.
		Logger& logger = LoggerFactory::getLogger("file.logger");
		logger.error(e.what());
		// Exit the application.
		return EXIT_FAILURE;
	}

	// Set the logger flags.
	Logger::setInfoEnabled(config.get<bool>("Logging.info_enabled"));
	Logger::setDebugEnabled(config.get<bool>("Logging.debug_enabled"));
	Logger::setWarningEnabled(config.get<bool>("Logging.warn_enabled"));
	Logger::setErrorEnabled(config.get<bool>("Logging.error_enabled"));

	// Create the factory that will generate the serializable services.
	Factory<ISerializableService, std::string> factory;
	// Register the serialization formats with their specified keys.
	factory.registerType("xml", std::make_unique<XmlSerializableService>());
	factory.registerType("lua", std::make_unique<LuaSerializableService>());

	// Initialize the resources.
	Resources resources;
	// Set the serializable service to the value found within the configuration file.
	resources.setService(factory.get(config.get<std::string>("Serialization.resource_format")));
	// Test there are no issues with loading the resources file.
    try
    {
		resources.load(config.get<std::string>("Core.resource_file"));
    }
    catch (NoResourceException& e)
    {
    	// Log that there was an issue opening or parsing the Resources.xxx file.
		Logger& logger = LoggerFactory::getLogger("file.logger");
		logger.error(e.what());
		// Exit the application.
        return EXIT_FAILURE;
    }

	Window window;
	window.create(config);

	// Create the temporary vertices.
	Vertex2D_t v1; v1.position = glm::vec2(-0.5f, -0.5f);
	Vertex2D_t v2; v2.position = glm::vec2( 0.5f, -0.5f);
	Vertex2D_t v3; v3.position = glm::vec2( 0.0f,  0.5f);
	// Populate an array of vertices.
	std::array<Vertex2D_t, 3> vertices;
	vertices.at(0) = v1;
	vertices.at(1) = v2;
	vertices.at(2) = v3;

	// Create a description for the buffer.
	BufferDescription desc;
	// "Zero" out the memory.
	memset(&desc, 0, sizeof(BufferDescription));
	// Populate the fields.
	desc.bufferType = gl::eBufferType::VERTEX;
	desc.drawType = gl::eDrawType::STATIC;
	desc.stride = sizeof(Vertex2D_t);
	desc.size = vertices.size();
	desc.pData = vertices.data();

	// Create the buffer with the description.
	Buffer buffer(desc);
	// Create the shader program.
	ShaderProgram program;
	// Attach two shaders.
	program.attach(gl::eShaderType::VERTEX, "data/shaders/basic_vertex.glsl");
	program.attach(gl::eShaderType::FRAGMENT, "data/shaders/basic_fragment.glsl");
	// Compile and link the shaders to the program.
	program.compile();

	// Continue to draw the window whilst it's running.
	while (window.isRunning())
	{
		// Clear the buffer.
		window.clear();
		// Bind the shader program.
		ShaderProgram::bind(program);
		// Bind and draw the vertex buffer.
		Buffer::bind(buffer);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		Buffer::unbind(buffer);
		// Unbind the shader program.
		ShaderProgram::bind(program);
		// Swap the buffers.
		window.swap();
	}

	// Closing the configuration file.
	config.close();
    // The application exited successfully.
    return EXIT_SUCCESS;
}
