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

#ifndef _PEGASUS_ASSET_HPP_
#define _PEGASUS_ASSET_HPP_

//====================
// C++ includes
//====================
#include <string> // Storing the name of the asset, for debugging purposes.

namespace pegasus
{
    //====================
    // Enumerations
    //====================
    enum class eAssetType
    {
        /** Asset type is a shader program. */
        SHADER,
        /** Asset type is a texture. */
        TEXTURE,
		/** Represents an erroneous asset type. */
		NONE
    };

    class Asset
    {
    protected:
        //====================
        // Member variables
        //====================
        /** Unique identifier of the asset. */
        unsigned int m_ID;
        /** The name of the asset, primarily used for debugging purposes. */
        std::string  m_name;
        /** The number of references to the asset object. */
        unsigned int m_references;

    public:
        //====================
        // Ctors and dtor
        //====================
        /**
         * @brief Default constructor for the Asset.
         * 
         * The default constructor will initialise all of the member variables
         * to default values. The reference count for the asset when constructed is 0.
         * Assets should never be dynamically allocated outside the use of the factory 
         * methods.
         */
        explicit Asset();

        /**
         * @brief Default destructor.
         */
        virtual ~Asset() = default;

        //====================
        // Getters and setters
        //====================
        /**
         * @brief Retrieves the ID of the asset.
         * 
         * The ID refers to the unique identifier of the asset, it is commonly 
         * used for binding behavior by the graphics API.
         * 
         * @returns The ID of the asset.
         */
        unsigned int getID() const;

        /**
         * @brief Retrieves the name of the asset.
         * 
         * The name of the asset is commonly used for debugging purposes, if 
         * any errors occurs during de-serialization or use.
         * 
         * @returns The name of the asset.
         */
        const std::string& getName() const;

        /**
         * @brief Sets the name of the asset.
         * 
         * The name of the asset is commonly used for debugging purposes, if 
         * any errors occurs during de-serialization or use.
         * 
         * @param name The new name of the asset.
         */
        void setName(const std::string& name);

        /** 
         * @brief Retrieves the current reference count of the asset.
         *
         * The reference count refers to the number of objects that are
         * currently referencing this asset, the asset will not be
         * destroyed whilst it is still retained.
         *
         * @returns The reference count of the Asset object.
         */
        unsigned int getRefCount() const;

        /* 
         * @brief Checks if the current asset is being referenced.
         *
         * An asset is counted as referenced if its' reference count
         * is greater than zero.
         * 
         * @breturns Whether the asset is referenced.
         */
        bool isReferenced() const;

        //====================
        // Methods
        //====================
        /**
         * @brief Retains the asset, preventing deletion.
         *
         * When a object is retained, it will prevent the object from
         * being de-allocated. Therefore this asset can be shared between
         * different objects without having to worry about manual memory
         * management. The asset will continue to be retained by its factory
         * unitl a set threshold is reached.
         */
        void retain();

        /**
         * @brief Releases a asset, allowing for potential deletion.
         *
         * When a asset is released, it will eventually be checked to see
         * if the object is still referenced, if the object is no longer referenced
         * and the factory threshold is reached, the asset will be de-allocated.
         */
        void release();
    };

} //namespace pegasus

#endif//_PEGASUS_ASSET_HPP_
