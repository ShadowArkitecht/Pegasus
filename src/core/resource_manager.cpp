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
// C++ includes
//====================  
#include <stdexcept> // Runtime exception throwing.

//==================== 
// Pegasus includes
//====================  
#include <pegasus/core/resource_manager.hpp> // Class declaration.

namespace pegasus
{
    //==================== 
    // Ctors and dtor
    //====================  
    /**********************************************************/
    ResourceManager::ResourceManager()
        : Singleton<ResourceManager>(), m_factories()
    {
        // Empty.
    }

    //==================== 
    // Methods
    //==================== 
    /**********************************************************/
    void ResourceManager::registerFactory(std::unique_ptr<IAssetFactory>&& factory)
    {
        // If the factory is null, throw an exception.
        if (factory.get() == nullptr)
        {
            throw std::runtime_error("Attempted to register a null factory.");
        }

        // Look to see if the factory has already been registered.
        auto itr = m_factories.find(factory->getType());
        // The factory has already been registered, throw an exception.
        if (itr != m_factories.end())
        {
			// TODO(Ben): Throw exception.
        }

        // Register the factory with the manager.
		m_factories.insert({ factory->getType(), std::move(factory) });
    }

} // namespace pegasus
