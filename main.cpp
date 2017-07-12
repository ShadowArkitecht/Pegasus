/*
* Sparky Engine
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

//====================
// Sparky includes
//====================
#include <sparky/utilities/logger.hpp>          // Creating different logging objects.
#include <sparky/utilities/console_policy.hpp>  // Registering the console policy with a logger.
#include <sparky/utilities/file_policy.hpp>     // Registering the file policy with a logger.
#include <sparky/utilities/logger_factory.hpp>  // Storing and retrieval of different logs.
#include <sparky/core/config_file.hpp>          // Loading the external configuration file.
#include <sparky/utilities/xml_serializable_service.hpp> // Registering the xml serializable service with a factory.
#include <sparky/utilities/lua_serializable_service.hpp> // Registering the lua serializable service with a factory.
#include <sparky/core/resources.hpp> // Loading and storing the Resources.xxx file.
#include <sparky/utilities/exceptions/no_resource_exception.hpp> // Caught if the Resources.xxx file fails to load.
#include <sparky/core/window.hpp>

using namespace sparky;

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
		config.open("config.sparky");
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

	while (window.isRunning())
	{
		window.clear();

		window.swap();
	}
	
	// Closing the configuration file.
	config.close();
    // The application exited successfully.
    return EXIT_SUCCESS;
}

