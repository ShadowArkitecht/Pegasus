#ifndef _SPARKY_ISERIALIZABlE_SERVICE_HPP_
#define _SPARKY_ISERIALIZABlE_SERVICE_HPP_

//==================== 
// C++ includes
//==================== 
#include <unordered_map>         // De-serialize the resources file.

//==================== 
// Sparky includes
//==================== 
#include <sparky/core/asset.hpp> // Need access to eAssetType enum class.

namespace sparky
{
    /**
     * @author Benjamin Carter
     *
     * @class sparky::ISerializableService
     * @ingroup utilities
     *
     * @brief Base service class that provides de-serialization methods for assets.
     *
     * This class is commonly invoked within the asset factory class to load external
     * serialized file formats into a asset class that can be utilised by the sparky engine.
     *
     * The class is provided as an interface so that the needed serialization functionality can
     * be injected into the factories. This complies with the IoC design pattern. Supported
     * serialization formats supported are xml, json and lua tables.
    */
    class ISerializableService
    {
    public:
        //==================== 
        // Ctors and dtor
        //==================== 
        /**
         * @brief Default constructor. 
         */
        explicit ISerializableService() = default;

        /** 
         * @brief Default destructor.
         */
        virtual ~ISerializableService() = default;

        //==================== 
        // Methods
        //==================== 
        /**
         * @brief Abstract method for de-serializing an object into an asset.
         *
         * This method is over-riden by any child classes that implement different de-serialization
         * methods. When this method is invoked, it will de-serialize an external file into the
         * specified asset so that it can be used within the sparky engine.
         *
         * @param type The type of asset to de-serialize the file into.
         * @param name The name of the resource to be de-serialized.
         *
         * @returns A pointer to a new de-serialized asset. 
         */
        virtual Asset* deserialize(eAssetType type, const std::string& name) const = 0;

		/**
		 * @brief Abstract method for de-serializaing all the resources in the specified files. 
		 *
		 * This method is overriden by any child classes that implement this class. When this method
		 * is invoked it will de-serialize all of the assets within the defined Resources file into a 
		 * format that the sparky engine can utilise.
		 * 
		 * @param filename The file location to load the Resources file from.
		 *
		 * @returns A list of all the assets within the resources file.
		 */
		virtual std::unordered_map<std::string, std::string> deserializeResources(const std::string& filename) const = 0;
    };

} // namespace sparky

#endif//_SPARKY_ISERIALIZABlE_SERVICE_HPP_
