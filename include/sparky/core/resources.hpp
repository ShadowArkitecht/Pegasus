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

#ifndef _SPARKY_RESOURCES_HPP_
#define _SPARKY_RESOURCES_HPP_

//==================== 
// C++ includes
//==================== 
#include <unordered_map> // Stores all of the resources and their locations.
#include <string>        // Stores the key and value of the resources.

namespace sparky
{
    /**
     * @author Benjamin Carter
     * 
     * @class sparky::Resources
     * @ingroup core
     *
     * @brief Loads and stores the file locations for all resources within the
     * sparky engine.
     *
     * The Resources class is a static class that is used to store the file
     * locations of all resources used within the Sparky Engine. The resources
     * are defined within the Resources.xml file, which maps a simple name to a
     * more complex file location.
     *
     * This class aids in retrieving resources from the ResourceManager with a
     * simpler naming convention that will not have to rely on hard-coded file
     * directories for caching and retrieval of assets.
     *
     * Below is a code example:
     * @code
     * // Load the resources from file.
     * Resources::load(); // This will load the Resources.xml by default.
     *
     * // Loads the file location of the base.texture object.
     * std::string file = Resources::get("base.texture");
     * @endcode
     */
    class Resources final
    {
    private:
        //==================== 
        // Member variables
        //==================== 
        /** Stores all of the file locations of the defined resources.*/
        static std::unordered_map<std::string, std::string> m_resources;

    public:
        //==================== 
        // Ctors and dtor
        //==================== 
        /**
         * @brief Default constructor.
         */
        explicit Resources() = default;

        /**
         * @brief Default destructor.
         */
        ~Resources() = default;
        

        //==================== 
        // Getters and setters
        //==================== 
        /**
         * @brief Retrieves a resources file location.
         *
         * When a resource is requested, it will utilitise the loaded
         * Resoures.xml file and search for the specified name. If the name is
         * found it will return the mapped file location. If the resource has
         * not been found, a NoResourceException will be thrown.
         *
         * @param name The name of the resource within the Resources.xml file.
         *
         * @returns The file location of the requested resource.
         * 
         * @throws NoResourceException If the resource is not found.
         */
        static std::string get(const std::string& name);
    
        //==================== 
        // Methods
        //==================== 
        /**
         * @brief Loads and parses all of the defined resource locations.
         *
         * This method is invoked before the sparky engine starts. It loads all
         * of the file directories of each resource, which can be retrieved from
         * a defined key. This aids in easier retrieval of resources, instead of
         * relying on file locations, which may change throughout the engines
         * development. If the file cannot be found, an exception will be
         * thrown.
         * 
         * @param filename The file location of the Resources.xml file.
         * 
         * @throws NoResourceException Thrown if the file cannot be found. 
         */
        static void load(const std::string& filename = "Resources.xml");
    };

} // namespace sparky

#endif//_SPARKY_RESOURCES_HPP_
