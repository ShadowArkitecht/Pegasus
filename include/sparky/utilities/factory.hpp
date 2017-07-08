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

#ifndef _SPARKY_FACTORY_HPP_
#define _SPARKY_FACTORY_HPP_

//==================== 
// Sparky includes
//====================  
#include <sparky/utilities/non_copyable.hpp> // The factory is not copyable or moveable.

//==================== 
// C++ includes
//====================  
#include <unordered_map> // Storing a list key value creator methods.
#include <functional>    // The creator is functional type.
#include <stdexcept>     // Throwing runtime errors if duplicate keys detected.

namespace sparky
{
	template <typename Type, typename Key>
	class Factory : NonCopyable
	{
	private:
		//==================== 
		// Member variables
		//====================  
		/** Stores a map of all the different creator functions for all the different keys. */
		std::unordered_map<Key, std::function<Type()>> m_creators;

	public:
		//==================== 
		// Ctors and dtor
		//====================  
		/**
		* @brief Default constructor for the Factory.
		*
		* The default constructor will initialise the member variables and call the parent NonCopyable
		* constructor.
		*/
		explicit Factory();

		/**
		* @brief Default destructor for the Factory.
		*/
		virtual ~Factory() = default;

		//==================== 
		// Getters and setters
		//====================
		/**
		* @brief Retrieves a resource from the factory.
		*
		* When the get method is invoked, it will find the element with the matching key and return
		* the value that is returned with the creator function is invoked. If the key cannot be found, a
		* out_of_range exception will be thrown.
		*
		* @param key The key of the creator to invoke.
		*
		* @returns The result of the creator method.
		*
		* @throws std::out_of_range If the key cannot be found within the factory.
		*/
		Type get(const Key& key) const;

		/**
		* @brief Retrieves a resource from the factory, or the default value.
		*
		* When the get method is invoked, it will find the element with the matching key and return
		* the value that is returned with the creator function is invoked. If the key cannot be found, The
		* default value passed in will be returned.
		*
		* @param key     The key of the creator to invoke.
		* @param default The default value if the key cannot be found.
		*
		* @returns The result of the creator method.
		*
		* @throws std::out_of_range If the key cannot be found within the factory.
		*/
		Type getOrDefault(const Key& key, Type default) const;

		//==================== 
		// Methods
		//====================  
		/**
		* @brief Registers a creator with the factory.
		*
		* When a resource is requested from the factory, if the specified key is found it will invoke
		* the creator method that is passed in this method. The creator object can either be a function
		* or method, but must return a unique_ptr of the templated Base type. If a duplicate key is detected
		* when registering the creator, a runtime error exception will be thrown.
		*
		* @param key     The key to register the creator with.
		* @param creator The function that will be invoked when an object is requested from the factory.
		*
		* @throws std::runtime_error If a duplicate key is registered with the factory.
		*/
		void registerType(const Key& key, const std::function<Type()>& creator);
	};

	//==================== 
	// Ctors and dtor
	//====================  
	/**********************************************************/
	template <typename Type, typename Key>
	Factory<Type, Key>::Factory()
		: NonCopyable()
	{
		// Empty.
	}

	//==================== 
	// Getters and setters
	//====================  
	/**********************************************************/
	template <typename Type, typename Key>
	Type Factory<Type, Key>::get(const Key& key) const
	{
		// This will throw a out_of_range exception if not found. 
		return m_creators.at(key)();
	}

	/**********************************************************/
	template <typename Type, typename Key>
	Type Factory<Type, Key>::getOrDefault(const Key& key, Type type) const
	{
		// Search for the key.
		auto itr = m_creators.find(key);
		// Found it, return the result of the creator.
		if (itr != m_creators.end())
		{
			return itr->second();
		}

		// Return the default value as the key wasn't found.
		return type;
	}

	//==================== 
	// Methods
	//====================  
	/**********************************************************/
	template <typename Type, typename Key>
	void Factory<Type, Key>::registerType(const Key& key, const std::function<Type()>& creator)
	{
		auto result = m_creators.insert({ key, creator });
		if (!result.second)
		{
			// Failed insertion (duplicate key). Throw exception.
			throw std::runtime_error("Cannot insert creator function into factory due to duplicate key.");
		}
	}

} // namespace sparky

#endif//_SPARKY_FACTORY_HPP_
