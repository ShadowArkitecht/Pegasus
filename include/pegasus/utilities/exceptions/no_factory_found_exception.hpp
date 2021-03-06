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

#ifndef _PEGASUS_NO_FACTORY_FOUND_EXCEPTION_HPP_
#define _PEGASUS_NO_FACTORY_FOUND_EXCEPTION_HPP_

//==================== 
// C++ includes
//====================  
#include <exception> // Inherits from the base exception class.
#include <string>    // Using a string as a message argument.

namespace pegasus
{
	/**
	* @author Benjamin Carter
	*
	* @class NoFactoryFoundException
	* @ingroup utilities
	*
	* @brief Exception class that is thrown when no factory is found within the
	* resource manager.
	*
	* This exception is pre-dominantly used within the ResourceManager when a 
	* resource is requested from the resource manager, if no related factory is
	* found, this exception will be thrown.
	*/
	class NoFactoryFoundException : public std::exception
	{
	public:
		//==================== 
		// Ctors and dtor
		//==================== 
		/**
		* @brief Creates a NoFactoryFoundException with a C-style message.
		*/
		explicit NoFactoryFoundException(const char* msg);

		/**
		* @brief Creates a NoFactoryFoundException with a C++ style message.
		*/
		explicit NoFactoryFoundException(const std::string& msg);

		/**
		* @brief Default destructor.
		*/
		~NoFactoryFoundException() throw() = default;

		//====================  
		// Methods
		//==================== 
		/**
		* @brief Retrieves the message associated with the exception.
		*
		* If a message needs to be logged when an exception has been thrown
		* and caught, this message can be used to display additional
		* information to the user and any relevant log files.
		*
		* @returns The message associated with the exception.
		*/
		const char* what() const throw();
	};

} // namespace pegasus

#endif//_PEGASUS_NO_FACTORY_FOUND_EXCEPTION_HPP_
