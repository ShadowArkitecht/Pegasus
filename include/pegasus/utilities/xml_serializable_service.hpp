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

#ifndef _PEGASUS_XML_SERIALIZABLE_SERVICE_HPP_
#define _PEGASUS_XML_SERIALIZABLE_SERVICE_HPP_

//==================== 
// Pegasus includes
//==================== 
#include <pegasus/utilities/iserializable_service.hpp>

namespace pegasus
{
	class XmlSerializableService final : public ISerializableService
	{
	public:
		//==================== 
		// Ctors and dtor
		//==================== 
		/**
		 * @brief Default constructor for the XmlSerializableService.
		 *
		 * The default constructor for the XmlSerializableService calls the
		 * ISerializableService parent constructor and initializes the member variables.
		 */
		explicit XmlSerializableService();

		/**
		 * @brief Default destructor. 
		 */
		~XmlSerializableService() = default;

		//==================== 
		// Methods
		//==================== 
		/**
		 * @brief Deserializes the specified asset into a format that the engine can utilise.
		 *
		 * When the asset is de-serialized, it will read in the resource in the specified directory and
		 * de-serialize the xml which is in a pre-determined tag format. if the resource is not found,
		 * a default asset will be returned to prevent undefined behavior.
		 *  
		 * @param type The asset type to de-serialize.
		 * @param name The name of the resource within the Resources.xml file
		 * 
		 * @returns A pointer to a Asset resource.
		 */
		Asset* deserialize(eAssetType type, const std::string& filename) const override;

		/**
		 * @brief De-serializes the Resources.xml into a format that the pegasus engine can utilise.
		 * 
		 * When the Resources.xml file is de-serialized, it will de-serialize each tag in the Resources node
		 * array. If the Resources file is not found or can't be opened, a NoResourceException will be thrown.
		 * 
		 * @param filename The file location of the Resources.xml file.
		 */
		std::unordered_map<std::string, std::string> deserializeResources(const std::string& filename) const override;
	};

} // namespace pegasus

#endif//_PEGASUS_XML_SERIALIZABLE_SERVICE_HPP_
