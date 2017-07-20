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

#ifndef _PEGASUS_SERIALIZE_EXCEPTION_HPP_
#define _PEGASUS_SERIALIZE_EXCEPTION_HPP_

//====================
// C++ includes
//====================
#include <stdexcept> // Is a type of exception.
#include <string>    // String can be used to define the exception message.

namespace pegasus
{
	class SerializeException final : public std::exception 
	{
	public:
		//====================
		// Ctors and dtor
		//====================
		/**
		* @brief Creates a SerializeException with a C-style message.
		*/
		explicit SerializeException(const char* msg);

		/**
		* @brief Creates a SerializeException with a C++ style message.
		*/
		explicit SerializeException(const std::string& msg);

		/**
		* @brief Default destructor.
		*/
		~SerializeException() throw() = default;

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

#endif//_PEGASUS_SERIALIZE_EXCEPTION_HPP_