#include <sparky/utilities/xml_serializable_service.hpp> // Class declaration.
#include <sparky/utilities/exceptions/no_resource_exception.hpp>    // Throwing exceptions if resource not found.

//====================
// Library includes
//====================
#include <pugixml.hpp> // De-serializing the Resources.xml file.

namespace sparky
{
	XmlSerializableService::XmlSerializableService()
		: ISerializableService()
	{
	}

	Asset* XmlSerializableService::deserialize(eAssetType type, const std::string& filename) const
	{
		return nullptr;
	}

	std::unordered_map<std::string, std::string> XmlSerializableService::deserializeResources(const std::string& filename) const
	{
		std::unordered_map<std::string, std::string> resources;

		// Load the xml document.
		pugi::xml_document document;
		pugi::xml_parse_result result = document.load_file(filename.c_str());

		// Check if it was successful.
		if (!result)
		{
			throw NoResourceException("Cannot open resource file: " + filename);
		}

		// Get the root "Resource" node. 
		pugi::xml_node root = document.child("Resources");
		for (auto& resource : root.children("Resource"))
		{
			resources.insert({ resource.child("Name").child_value() , resource.child("Source").child_value() });
		}

		return resources;
	}

} // namespace sparky