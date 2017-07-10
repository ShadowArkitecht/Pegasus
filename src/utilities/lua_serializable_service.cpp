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
#include <sparky/utilities/lua_serializable_service.hpp>         // Class declaration.
#include <sparky/scripting/scripting_manager.hpp>                // Retrieving the lua state.
#include <sparky/utilities/exceptions/no_resource_exception.hpp> // Throwing an exception if there were any issues with the resource handling.

namespace sparky
{
	//====================
	// Ctors and dtor
	//====================
	/**********************************************************/
	LuaSerializableService::LuaSerializableService()
		: ISerializableService()
	{
	}

	//====================
	// Methods
	//====================
	/**********************************************************/
	Asset* LuaSerializableService::deserialize(eAssetType type, const std::string& name) const
	{
		// TODO(Ben): De-serialize.
		return nullptr;
	}

	/**********************************************************/
	std::unordered_map<std::string, std::string> LuaSerializableService::deserializeResources(const std::string& filename) const
	{
		// Retrieve the lua state.
		sol::state& lua = ScriptingManager::getInstance().getState();
		// Load the specified script.
		sol::function_result result = lua.script_file(filename);
		// Check if there are no issues with the script, if there is, throw an exception.
		if (!result.valid())
		{
			throw NoResourceException("Cannot open resource file: " + filename);
		}
		// Grab the root table.
		sol::table root = lua["resources"];
		// Populate the resources being stored in the table.
		std::unordered_map<std::string, std::string> resources;
		for (std::size_t i = 0; i < root.size(); i++)
		{
			sol::table resource = root[i + 1];
			// Check to see the resource elements exist.
			std::string name = resource.get_or("name", std::string());
			std::string source = resource.get_or("source", std::string());

			// The names don't exist, log an error.
			if (name.empty() || source.empty())
			{
				// TODO(Ben): Log issue.
			}

			resources.insert({ name, source });
		}

		return resources;
	}

} // namespace sparky