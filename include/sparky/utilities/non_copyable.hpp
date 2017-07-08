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

#ifndef _SPARKY_NON_COPYABLE_HPP_
#define _SPARKY_NON_COPYABLE_HPP_

namespace sparky
{
    /**
     * @author Benjamin Carter
     *
     * @class sparky::NonCopyable
     * @ingroup utilities
     *
     * @brief Parent class that prevents child classes from being copyable.
     *
     * When an class inherits from the NonCopyable class, it prevents the object
     * from being constructed or assigned with either a reference or moved
     * object of the same type. This class is only utilised by classes that
     * may be erroneous if copied, such as a Window instance or singleton
     * classes.
     */
    class NonCopyable
    {
    private:
        //==================== 
        // Private ctors.
        //==================== 
        /**
         * @brief Deleted copy constructor.
         *
         * This prevents any child classes from constructing an object with
         * another object of the same time.
         * 
         * @param The non copyable object that will not be copied.
         */
        explicit NonCopyable(const NonCopyable&) = delete;

        /**
         * @brief Deleted move constructor.
         *
         * This prevents any child classes from being created by utilising move
         * semantics.
         *
         * @param The non copyable object that will not be moved. 
         */
        explicit NonCopyable(NonCopyable&&) = delete;

        //==================== 
        // Private operators
        //==================== 
        /** 
         * @brief Deleted assignment operator.
         *
         * This deleted operator prevents the object from being assigned to
         * another object of the same type.
         * 
         * @param The object that this object will not be assigned to.
         * 
         * @returns A reference to this non copyable object.
         */
        NonCopyable& operator=(const NonCopyable&) = delete;

        /**
         * @brief Deleted move assignment operator.
         *
         * This deleted operator prevents the moved object being assigned to
         * another move assigned object.
         *
         * @param The object this non copyable object will not be moved from.
         *
         * @returns The moved non copyable object.
         */
        NonCopyable&& operator=(NonCopyable&&) = delete;

    public:
        //==================== 
        // Ctors and dtor
        //==================== 
        /**
         * @brief Default constructor.
         */
        explicit NonCopyable() = default;

        /**
         * @brief Default destructor.
         */
        virtual ~NonCopyable() = default;
    };

} // namespace sparky

#endif//_SPARKY_NON_COPYABLE_HPP_
