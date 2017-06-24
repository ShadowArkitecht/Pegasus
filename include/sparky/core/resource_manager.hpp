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

#ifndef _SPARKY_RESOURCE_MANAGER_HPP_
#define _SPARKY_RESOURCE_MANAGER_HPP_

//==================== 
// C++ includes
//==================== 
#include <unordered_map> // Store the factories in a map.

//==================== 
// Sparky includes
//====================
#include <sparky/utilities/iasset_factory.hpp> // Contains a list of factories.
#include <sparky/utilities/no_factory_found_exception.hpp> // No factory found.

namespace sparky
{
    class ResourceManager final
    {
    private:
        /** A map of all registered asset factories within the manager. */
        std::unordered_map<std::type_index, IAssetFactory*> m_factories;

    public:
        //==================== 
        // Ctors and dtor
        //==================== 
        /**
         * @brief Constructor for the ResourceManager.
         *
         * The constructor is called when the ResourceManager instance is
         * registered. It will initialise the map needed to retain all of the
         * asset factories.
         */
        explicit ResourceManager();

        /**
         * @brief Destructor for the ResourceManager.
         *
         * The ResourceManager is responsible for the lifetime of the registered
         * factories. When the destructor is called, all of the factories will
         * be de-allocated and the map cleared.
         */
        ~ResourceManager();

        //==================== 
        // Getters and setters 
        //==================== 
        /**
         * @brief Retrieves a resource of the specified type from the manager.
         *
         * When a resource is requested, it will attempt to utilise the factory
         * registered with this type to load the resource. If the factory is
         * found, a new resource is either created or pulled from the factories
         * cache and returned to the user. If a factory for the type has not
         * been registed, a NoFactoryFoundException will be thrown.
         * 
         * @tparam T The asset to retrieve from the manager.
         * @param name The name of the asset to retrieve.
         *
         * @returns A loaded/cached resource of the requested type.
         *
         * @throws NoFactoryFoundException No factory has been registered for
         * the asset type.
         */
        template <typename T>
        T* get(const std::string& name) const;

        //==================== 
        // Methods
        //==================== 
        /**
         * @brief Registers a factory with the manager.
         *
         * When a factory is registered with the ResourceManager, it will be
         * used to construct objects of a specific type when a resource is
         * requested from the manager, depending on the type requested. Only one
         * factory of each type can be registered with the manager, an exception
         * will be thrown if a duplicate is detected or the factory is null.
         *
         * @param pFactory The factory to register with the manager.
         *
         * @throws std::runtime_error If the factory has already been registered
         * or is equal to nullptr.
         */
        void registerFactory(IAssetFactory* pFactory);
    };

    //==================== 
    // Methods
    //==================== 
    /**********************************************************/
    template <typename T>
    T* ResourceManager::get(const std::string& name) const
    {
        // Search the factories.
        auto itr = m_factories.find(typeid(T));
        // No factory was found, throw the exception.
        if (itr == m_factories.end())
        {
            // TODO(Ben): Throw a NoFactoryFoundException.
			throw NoFactoryFoundException("No factory for object type has been registered");
        }

        // Attempt to load the resource with the factory.
        return itr->second->load(name);
    } 

} // namespace sparky

#endif//_SPARKY_RESOURCE_MANAGER_HPP_
