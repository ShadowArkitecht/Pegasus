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

#ifndef _PEGASUS_IASSET_FACTORY_HPP_
#define _PEGASUS_IASSET_FACTORY_HPP_

//====================
// C++ includes
//====================
#include <memory> // The serializable service is stored as a smart pointer.
#include <typeindex> // Stores the type the factory is registered with.
#include <string> // Retrieving assets from the resource name.

//==================== 
// Pegasus includes
//==================== 
#include <pegasus/utilities/non_copyable.hpp> // The factory cannot be copied.
#include <pegasus/utilities/iserializable_service.hpp> // The serializable service for the asset factory.

namespace pegasus
{
	//====================
	// Forward declarations.
	//====================
    class Asset;

	/**
	 * @author Benjamin Carter
	 * 
	 * @class pegasus::IAssetFactory
	 * @ingroup utilities
	 * 
	 * @brief Base abstract class for all resource-related factories.
	 * 
	 * The IAssetFactory class is the parent class for factories relating to asset management within the Pegasus
	 * Engine. It provides a pure virtual method for loading assets from a specified location into memory so that it
	 * can be utilised by the application. The majority of asset factories will cache resources to prevent duplication
	 * of data. 
	 * 
	 * Each factory is assigned a unique type upon construction. The type is used when the factory is registered with the
	 * ResourceManager. The type is then utilised to retrieve the correct factory when requesting resources through the manager.
	 * There cannot be multiple factories registered to the same type, each factory is uniquely defined. The life-time of each
	 * factory is managed through the ResourceManager object, and should not be manually deleted outside this scope.
	 * 
	 * An implementation of the IAssetFactory abstract class is provided with the TextureFactory class. 
	 */
	class IAssetFactory : public NonCopyable
	{
	private:
		//====================
		// Member variables
		//====================
        /** The injected serialization method this factory will utilitize. */
        ISerializableService* m_pService;
		/** The unique object type that this asset factory is bound to/will produce. */
	    std::type_index       m_type; 
		/** The threshold in which un-used resources will be cleared from memory. */
	    std::size_t           m_threshold;
	    
	private:
		//====================
		// Private ctors
		//====================
		/**
		 * @brief Default constructor for the asset factory.
		 * 
		 * The default constructor for the asset factory is deleted. The factory must have a definition
		 * for the name and type_index supplied at construction for correct behavior when being registered with
		 * the ResourceManager. 
		 */
		explicit IAssetFactory() = delete;
		
		/**
		 * @brief Copy constructor for the asset factory.
		 * 
		 * The copy constructor for the IAssetFactory is deleted. Many of the factories retain their resources and
		 * use reference counted objects. Copying the factory may cause duplicate references or cause resources to be
		 * de-allocated at incorrect times. 
		 * 
		 * @param The factory that will not be copied. 
		 */
		explicit IAssetFactory(IAssetFactory&) = delete;
	    
	public:
		//====================
		// Ctors and dtor
		//====================
		/**
		 * @brief IAssetFactory constructor with definitions for name and type.
		 * 
		 * This constructor is the only publically available constructor to all child factory classes. When a factory is
		 * registered with the ResourceManager, it uses the std::type_index to define which resources individual factories
		 * will be responsible for. Only one factory of a specific type can be registed with the ResourceManager.
		 * 
		 * @param type      The resource type that this asset factory will be bound to when requesting resources.
		 * @param threshold How many resources can be retained before un-referenced resources will be cleared from memory.
		 */
	    explicit IAssetFactory(const std::type_index& type, std::size_t threshold = 10);
	    
	    /**
	     * @brief Default destructor.
	     */
	    virtual ~IAssetFactory() = default;
	    
	    //====================
		// Getters and setters
		//====================
        /**
         * @brief Retrieves the serializable service from the factory.
         *
         * The serializable service is responsible for de-serializing any external files that this
         * factory is provided and converted them into a format that the pegasus engine can utlitize.
         * Various different serialization methods are supported so the functionality must be
         * injected into the factory before use.
         *
         * @returns The serializable service injected into this factory.
         */
        ISerializableService* getService() const;

        /**
         * @brief Injects the serializable service into the factory. 
         *
         * The serializable service is responsible for de-serializing any external files that this
         * factory is provided and converted them into a format that the pegasus engine can utlitize.
         * Various different serialization methods are supported so the functionality must be
         * injected into the factory before use.
         *
         * @param service The serializable service to be injected into the factory.
         */
        void setService(ISerializableService& service);

	    /**
	     * @brief Retrieves the type registed with this factory.
	     * 
	     * Each factory is assigned a unique type upon construction. The type refers to the type of resource this factory will
	     * manage the creation and lifetime of. The type is also used to retrieve the correct factory when requesting resources
	     * via the ResourceManager. Only one factory of each type can be registered.
	     * 
	     * @returns The resource type this factory is bound to.
	     */
	    const std::type_index& getType() const;
	    
	    /**
	     * @brief Retrieves the current threshold of the factory.
	     * 
	     * The threshold refers to the number of resources that will be retained before un-used resources are deleted and cleared
	     * from the cache. This is to prevent resources which may be constantly referenced and de-referenced from being removed from
	     * memory immediately. The default threshold for all factories is 10. 
	     * 
	     * @returns The memory threshold of the factory.
	     */
	    std::size_t getThreshold() const;
	    
	    /**
	     * @brief Sets the new threshold of the factory.
	     * 
	     * The threshold refers to the number of resources that will be retained before un-used resources are deleted and cleared
	     * from the cache. This is to prevent resources which may be constantly referenced and de-referenced from being removed from
	     * memory immediately. The default threshold for all factories is 10. It should be noted that the higher the threshold, the
	     * more memory intensive the factory will become.
	     * 
	     * @param threshold The new threshold of the factory.
	     */
	    void setThreshold(std::size_t threshold);
	    
	    //====================
		// Methods
		//====================
	    /**
	     * @brief Loads an asset from the factory. 
	     * 
	     * Pure virtual method. Each factory will deal with the implementation and loading of resources in different manners. 
	     * Commonly the factories will cache resources and re-use them when possible to prevent duplication of data. If the 
	     * loading of a resource fails, a default resource is returned an a warning is logged. 
	     * 
	     * @param name  The name of the resource within the Resources.xml file.
	     * 
	     * @returns The request asset, or a default resource if retrieval fails.
	     */
	    virtual Asset* load(const std::string& name) = 0;
	};
	
} // namespace pegasus

#endif//_PEGASUS_IASSET_FACTORY_HPP_
