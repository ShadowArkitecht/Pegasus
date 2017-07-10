#include <cstdlib>

#include <sparky/utilities/logger.hpp>
#include <sparky/utilities/console_policy.hpp>
#include <sparky/utilities/file_policy.hpp>

#include <sparky/utilities/logger_factory.hpp>

#include <sparky/core/config_file.hpp>
#include <sparky/utilities/factory.hpp>
#include <sparky/utilities/xml_serializable_service.hpp>
#include <sparky/utilities/lua_serializable_service.hpp>
#include <sparky/core/resources.hpp>
#include <sparky/utilities/exceptions/no_resource_exception.hpp>

using namespace sparky;

int main(int argc, char** argv)
{
	// Load the custom config/ini file.
	ConfigFile config("config.sparky");
	// Set the logger flags.
	Logger::setInfoEnabled(config.get<bool>("Logging.info_enabled"));
	Logger::setDebugEnabled(config.get<bool>("Logging.debug_enabled"));
	Logger::setWarningEnabled(config.get<bool>("Logging.warn_enabled"));
	Logger::setErrorEnabled(config.get<bool>("Logging.error_enabled"));
	// Create a logger object that will print messages to the console.
	auto cl = std::make_unique<Logger>(std::make_unique<ConsolePolicy>());
	// Create a logger object that will send messages to an external file.
	auto fl = std::make_unique<Logger>(std::make_unique<FilePolicy>("log.txt"));
	// Register the console logger with the factory.
	LoggerFactory::registerLogger("console.logger", std::move(cl));
	LoggerFactory::registerLogger("file.logger", std::move(fl));
	
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
		Logger& logger = LoggerFactory::getLogger("file.logger");
		logger.error(e.what());

        return EXIT_FAILURE;
    }

    getchar();
    return EXIT_SUCCESS;
}

