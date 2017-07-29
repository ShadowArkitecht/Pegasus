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

#ifndef _PEGASUS_LUA_SERIALIZABLE_SERVICE_HPP_
#define _PEGASUS_LUA_SERIALIZABLE_SERVICE_HPP_

//==================== 
// Pegasus includes
//====================  
#include <pegasus/utilities/iserializable_service.hpp> // LuaSerializableService is a serializable service.

namespace pegasus
{
	//====================
	// Forward declarations
	//====================
	class Logger;

	class LuaSerializableService final : public ISerializableService
	{
	private:
		//====================
		// Member variables
		//====================
		/** Logging warnings from the Resources.lua file. */
		Logger& m_logger;

	private:
		//====================
		// Private methods
		//====================
		/**
		 * @brief De-serializes an asset into a shader program object.
		 * 
		 * This method is invoked internally when an object is de-serializaed and it
		 * is flagged as a shader program. This object will de-serialize the lua table into
		 * a format that can be used to bind and utilize different shaders within a program.
		 * The de-serialization of the shader will fail if no shaders have been defined.
		 * 
		 * @param name The file location of the lua script to de-serialize.
		 * 
		 * @returns A new shader program object.
		 */
		Asset* deserializeShaderProgram(const std::string& name) const;

		/**
		 * @brief De-serializes an asset into a Texture object.
		 * 
		 * This method is invoked internally when an object is de-serializaed and it
		 * is flagged as a texture. This object will de-serialize the lua table into
		 * a format that can be used to bind and utilize different textures within the application.
		 * The de-serialization of the texture will fail if no image source has been defined.
		 * 
		 * @param name The file location of the lua script to de-serialize.
		 * 
		 * @returns A new Texture object.
		 */		
		Asset* deserializeTexture(const std::string& name) const;

	public:
		//==================== 
		// Ctors and dtor
		//====================  
		/**
		 * @brief Default constructor for the LuaSerializableService.
		 *
		 * The default constructor for the LuaSerializableService calls the
		 * ISerializableService parent constructor and initializes the member variables.
		 */
		explicit LuaSerializableService();

		/**
		 * @brief Default destructor. 
		 */
		~LuaSerializableService() = default;

		//==================== 
		// Methods
		//====================  
		/**
		 * @brief Deserializes the specified asset into a format that the engine can utilise.
		 *
		 * When the asset is de-serialized, it will read in the resource in the specified directory and
		 * de-serialize the lua which is in a pre-determined table format. if the resource is not found,
		 * a default asset will be returned to prevent undefined behavior.
		 *  
		 * @param type The asset type to de-serialize.
		 * @param name The name of the resource within the Resources.xxx file
		 * 
		 * @returns A pointer to a Asset resource.
		 */
		Asset* deserialize(eAssetType type, const std::string& name) const override;

		/**
		 * @brief De-serializes the Resources.lua into a format that the pegasus engine can utilise.
		 * 
		 * When the Resources.lua file is de-serialized, it will de-serialize each table in the Resources table
		 * array. If the Resources file is not found or can't be opened, a NoResourceException will be thrown.
		 * 
		 * @param filename The file location of the Resources.lua file.
		 * 
		 * @returns A map of resources and their subsequent names.
		 */
		std::unordered_map<std::string, Resource_t> deserializeResources(const std::string& filename) const override;
	};

} // namespace pegasus

#endif//_PEGASUS_LUA_SERIALIZABLE_SERVICE_HPP_
