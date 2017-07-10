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
// Sparky includes
//====================
#include <sparky/utilities/xml_serializable_service.hpp> // Class declaration.
#include <sparky/utilities/exceptions/no_resource_exception.hpp>    // Throwing exceptions if resource not found.

//====================
// Library includes
//====================
#include <pugixml.hpp> // De-serializing the Resources.xml file.

namespace sparky
{
	//====================
	// Ctors and dtor
	//====================
	/**********************************************************/
	XmlSerializableService::XmlSerializableService()
		: ISerializableService()
	{
	}

	//====================
	// Methods
	//====================
	/**********************************************************/
	Asset* XmlSerializableService::deserialize(eAssetType type, const std::string& filename) const
	{
		return nullptr;
	}

	/**********************************************************/
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