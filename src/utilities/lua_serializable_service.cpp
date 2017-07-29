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
// Pegasus includes
//====================
#include <pegasus/utilities/lua_serializable_service.hpp>         // Class declaration.
#include <pegasus/utilities/logger_factory.hpp>                   // Logging any Resources.lua de-serialization issues.
#include <pegasus/scripting/scripting_manager.hpp>                // Retrieving the lua state.
#include <pegasus/utilities/exceptions/no_resource_exception.hpp> // Throwing an exception if there were any issues with the resource handling.
#include <pegasus/graphics/shader_program.hpp>                    // De-serializing shader program objects.
#include <pegasus/utilities/exceptions/serialize_exception.hpp>   // Throwing errors if any de-serialization has failed.
#include <pegasus/graphics/texture.hpp>                           // De-serializing texture objects.

namespace pegasus
{
	//====================
	// Ctors and dtor
	//====================
	/**********************************************************/
	LuaSerializableService::LuaSerializableService()
		: ISerializableService(), m_logger(LoggerFactory::getLogger("file.logger"))
	{
		// Empty.
	}

	//====================
	// Private methods
	//====================
	/**********************************************************/
	Asset* LuaSerializableService::deserializeShaderProgram(const std::string& name) const
	{
		// Retrieve the lua state.
		sol::state& lua = ScriptingManager::getInstance().getState();
		// Load the specified script.
		sol::function_result result = lua.script_file(name);
		// Check if there are no issues with the script, if there is, throw an exception.
		if (!result.valid())
		{
			throw SerializeException(std::string("Unable to de-serialize file:") + name);
		}

		// Get the root of the shader program.
		sol::table root = lua["ShaderProgram"];
		// Get the variables
		// Retrieve the name of the shader, if it's not defined, just set it to an empty string.
		std::string shaderName = root.get_or("name", std::string());
		// Get the array of shaders to define.
		sol::table shaders = root.get_or("shaders", sol::table());
		if (shaders.empty())
		{
			throw SerializeException(std::string("No glsl shaders have been defined in file:") + name);
		}
		
		// Create the shader program.
		ShaderProgram* pProgram = new ShaderProgram();
		// Set the debu name.
		pProgram->setName(shaderName);
		// Loop through each attached shader.
		for (std::size_t i = 0; i < shaders.size(); i++)
		{
			// Retrieve the shader definition.
			sol::table shader = shaders[i + 1];
			// Get the name and type of the shader defined.
			std::string source = shader.get_or("source", std::string());
			// Get the shader type.
			sol::object st = shader["shader_type"];
			gl::eShaderType type = st.as<gl::eShaderType>();
			// Attach the shader as an object within the program.
			pProgram->attach(type, source);
		}
		// Return the shader.
		return pProgram;
	}

	/**********************************************************/
	Asset* LuaSerializableService::deserializeTexture(const std::string& name) const
	{
		// Retrieve the lua state.
		sol::state& lua = ScriptingManager::getInstance().getState();
		// Load the specified script.
		sol::function_result result = lua.script_file(name);
		// Check if there are no issues with the script, if there is, throw an exception.
		if (!result.valid())
		{
			throw SerializeException(std::string("Unable to de-serialize file:") + name);
		}

		// Get the root of the texture.
		sol::table root = lua["Texture"];
		// Get the variables
		// Retrieve the name of the shader, if it's not defined, just set it to an empty string.
		std::string textureName = root.get_or("name", std::string());
		// Get the texture type.
		sol::object type = root["texture_type"];
		// Get the image source.
		std::string source = root.get_or("source", std::string());
		// There is no image, throw an exception.
		if (source.empty())
		{
			throw SerializeException(std::string("No image source has been declared in file:") + name);
		}
		// Get the wrapping mode.
		sol::object wrap = root["wrap_mode"];
		// Get the filtering mode.
		sol::object filter = root["filter"];
		// Create a texture description and populate its values.
		TextureDescription_t desc;
		memset(&desc, 0, sizeof(TextureDescription_t));

		desc.source = source;
		desc.type = type.as<gl::eTextureType>();
		desc.filtering = filter.as<gl::eFilterType>();
		desc.wrapping = filter.as<gl::eWrapType>();
		// Create the texture from the description and return it.
		return new Texture(desc);
	}

	//====================
	// Methods
	//====================
	/**********************************************************/
	Asset* LuaSerializableService::deserialize(eAssetType type, const std::string& name) const
	{
		switch (type)
		{
		case eAssetType::SHADER:
			return this->deserializeShaderProgram(name);

		case eAssetType::TEXTURE:
			return this->deserializeTexture(name);
		}

		return nullptr;
	}

	/**********************************************************/
	std::unordered_map<std::string, Resource_t> LuaSerializableService::deserializeResources(const std::string& filename) const
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
		sol::table root = lua["Resources"];
		// Populate the resources being stored in the table.
		std::unordered_map<std::string, Resource_t> resources;
		for (std::size_t i = 0; i < root.size(); i++)
		{
			sol::table r = root[i + 1];
			// Check to see the resource elements exist.
			std::string name = r.get_or("name", std::string());

			// The names don't exist, log a warning.
			if (name.empty())
			{
				m_logger.warning("Resource unable to de-serialize correctly. A name has not been defined.");
				continue;
			}
			
			std::string source = r.get_or("source", std::string());
			sol::object type = r["asset_type"];

			Resource_t resource;
			resource.path = source;
			resource.type = type.as<eAssetType>();

			resources.insert({ name, resource });
		}

		return resources;
	}

} // namespace pegasus
