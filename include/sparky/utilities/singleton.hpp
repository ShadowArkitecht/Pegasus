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

#ifndef _SPARKY_SINGLETON_HPP_
#define _SPARKY_SINGLETON_HPP_

//==================== 
// Sparky includes
//==================== 
#include <sparky/utilities/non_copyable.hpp> // Singleton is a non-copyable object.

namespace sparky
{
    /**
     * @author Benjamin Carter
     *
     * @class Singleton<T>
     * @ingroup utilities
     *
     * @brief Generic implementation of the GoF singleton design pattern.
     *
     * This templated class is a generic implementation of the GoF singleton
     * design pattern, it is utilised by any managers within the application
     * (such as the ResourceManager) that are accessed within various different
     * module of the application and need global scope. 
     */
    template <typename T>
    class Singleton : public NonCopyable
    {
    protected:
        //==================== 
        // Protected ctors
        //==================== 
        /**
         * @brief Default constructor for the Singleton object.
         *
         * The constructor of the Singleton object is protected as the
         * singleton object instance should be created outside the scope of this
         * class or its' subsequent children. This is to conform with the GoF
         * singleton pattern.
         */
        explicit Singleton(); 

    public:
        //==================== 
        // Dtor
        //==================== 
        /**
         * @brief Default destructor for the Singleton object.
         */
        virtual ~Singleton() = default;

        //==================== 
        // Getters and setters
        //==================== 
        /**
         * @brief Retrieves the instance of the singleton.
         *
         * In order to access the methods and variables of any singleton object,
         * its static instance is exposed to the user. The instance is
         * constructed when the singleton is first used and destroys when
         * program execution ends. 
         *
         * @returns A reference to the static instance of the singleton.
         */
        static T& getInstance();
    };

    //==================== 
    // Ctors
    //==================== 
    /**********************************************************/
    template <typename T>
    Singleton<T>::Singleton()
        : NonCopyable()
    {
        // Empty.
    }

    //====================  
    // Getters and setters
    //==================== 
    /**********************************************************/
    template <typename T>
    T& Singleton<T>::getInstance()
    {
        static T instance;
        return instance;
    }

} // namespace sparky

#endif//_SPARKY_SINGLETON_HPP_
