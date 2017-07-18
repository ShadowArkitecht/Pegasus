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

#ifndef _PEGASUS_LOGGER_FACTORY_HPP_
#define _PEGASUS_LOGGER_FACTORY_HPP_

//==================== 
// C++ includes
//====================  
#include <pegasus/utilities/factory.hpp> // Factory for creating and storing different Logger objects.
#include <pegasus/utilities/logger.hpp>  // Storing logger objects.

namespace pegasus
{
	class LoggerFactory final
	{
	private:
		//==================== 
		// Member variables
		//====================  
		/** Storing and retrieving different logging objects. */
		static Factory<Logger, std::string> m_factory;

	public:
		//==================== 
		// Ctors and dtor
		//====================  
		/**
		 * @brief Default constructor for the LoggerFactory.
		 */
		explicit LoggerFactory() = default;

		/**
		 * @brief Default destructor for the LoggerFactory.
		 */
		~LoggerFactory() = default;

		//==================== 
		// Getters and setters
		//====================  
		/**
		 * @brief Retrieves a Logger instance from the factory.
		 *
		 * When a logger is requested from the factory, it will check if the logging resource
		 * has been registered. If the key has not been registered, a out_of_range exception will be
		 * thrown.
		 *
		 * @param name The name/key of the logger to retrieve.
		 *
		 * @throws out_of_range exception if the key has not been registered.
		 *
		 * @returns The Logger instance associated with the key.
		 */
		static Logger& getLogger(const std::string& name);

		//==================== 
		// Methods
		//====================  
		/**
		 * @brief Registers a logger with the factory.
		 *
		 * the register method is just a thin wrapper around the Factory::registerType method. If
		 * a duplicate type is attempted to be registered, a runtime_error will be thrown.
		 *
		 * @param name The name/key to register the logger against.
		 * @param logger The logger instance to register.
		 *
		 * @throws runtime_error If a duplicate key has been detected when registering.
		 */
		static void registerLogger(const std::string& name, std::unique_ptr<Logger> logger);
	};

} // namespace pegasus

#endif//_PEGASUS_LOGGER_FACTORy_HPP_
