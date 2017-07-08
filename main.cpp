#include <cstdlib>

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

	// Create the factory that will generate the serializable services.
	Factory<std::unique_ptr<ISerializableService>, std::string> factory;
	// Register the serialization formats with their specified keys.
	factory.registerType("xml", std::make_unique<XmlSerializableService>);
	factory.registerType("lua", std::make_unique<LuaSerializableService>);

	// Initialize the resources.
	Resources resources;
	// Set the serializable service to the value found within the configuration file.
	resources.setService(factory.get(config.get<std::string>("Serialization.resource_format")));

	// Test there are no issues with loading the resources file.
    try
    {
		resources.load(config.get<std::string>("Core.resource_file"));
    }
    catch (NoResourceException&)
    {
		// The resources file failed to load, log the reason why and quit the application.
        // TODO(Ben): Log this exception.
        return EXIT_FAILURE;
    }

    getchar();
    return EXIT_SUCCESS;
}

