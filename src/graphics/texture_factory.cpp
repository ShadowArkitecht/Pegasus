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
#include <pegasus/graphics/texture_factory.hpp>                   // Class declaration.
#include <pegasus/graphics/texture.hpp>                           // Loading in and storing shader programs.
#include <pegasus/utilities/logger.hpp>                           // Logging messages within factories.
#include <pegasus/utilities/exceptions/serialize_exception.hpp>   // Catching any thrown serialize exceptions.
#include <pegasus/utilities/exceptions/no_resource_exception.hpp> // Catching any thrown resource exceptions.

namespace pegasus
{
	//====================
	// Ctors and dtor
	//====================
	/**********************************************************/
	TextureFactory::TextureFactory()
		: IAssetFactory(typeid(Texture))
	{
		m_logger.debug("TextureFactory constructed.");
	}

	//====================
	// Methods
	//====================
	/**********************************************************/
	Asset* TextureFactory::load(const std::string& name) // override
	{
		// Check the threshold, and delete any non-referenced objects.
		this->checkThreshold();
		
		try
		{
			Resource_t resource = m_resources.get(name);
			// See if the texture being requested has already been loaded.
			auto itr = m_assets.find(resource.path);
			// It has been found, return a copy of that object.
			if (itr != m_assets.end())
			{
				return itr->second;
			}
			// De-serialize and create a new texture.
			auto texture = this->getService()->deserialize(eAssetType::TEXTURE, resource.path);
			// Insert the texture into the map.
			m_assets.insert({ resource.path, texture });
			// Return the new texture.
			return texture;
		}
		catch (SerializeException& e)
		{
			m_logger.warning("TextureFactory:", e.what(), ". Returning default texture asset.");
			return Texture::getDefault();
		}
		// Catch a wrong resource and return the default.
		catch (NoResourceException& e)
		{
			m_logger.warning("TextureFactory:", e.what(), ". Returning default texture asset.");
			return Texture::getDefault();
		}
		// Might aswell catch all, incase there's any problems that we're not expected.
		catch (std::exception& e)
		{
			m_logger.warning("TextureFactory:", e.what(), ". Returning default texture asset.");
			return Texture::getDefault();
		}
	}

} // namespace pegasus