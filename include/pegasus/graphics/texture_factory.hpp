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

#ifndef _PEGASUS_TEXTURE_FACTORY_HPP_
#define _PEGASUS_TEXTURE_FACTORY_HPP_

//====================
// Pegasus includes
//====================
#include <pegasus/utilities/iasset_factory.hpp> // The factory is a type of asset factory.

namespace pegasus
{	
	class TextureFactory final : public IAssetFactory
	{
	public:
		//====================
		// Ctors and dtor
		//====================
		/**
		 * @brief Default constructor for the texture factory.
		 * 
		 * The default constructor will set the member variables to default
		 * values and set the logger to log messages to the external log file.
		 */
		explicit TextureFactory();

		/**
		 * @brief Default destructor.
		 */
		~TextureFactory() = default;

		/**
		 * @brief Loads an external serialized file and stores it as an asset.
		 * 
		 * When the load method is invoked, it will use the bound serializable
		 * service to de-serialize the specified asset and store it in a map object.
		 * If the object has already been loaded, it will use the retained resource, instead
		 * of re-creating an identical object.
		 * 
		 * @param name The name of the asset to retrieve.
		 * @returns The asset being loaded.
		 */
		Asset* load(const std::string& name) override;
	};

} // namespace pegasus

#endif//_PEGASUS_TEXTURE_FACTORY_HPP_