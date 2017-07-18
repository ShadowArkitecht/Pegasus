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

#ifndef _PEGASUS_LOGGER_HPP_
#define _PEGASUS_LOGGER_HPP_

//====================
// C++ includes
//====================
#include <memory>  // Policies are stored as unique pointers.
#include <sstream> // Storing the results of the logging writing.
#include <string>  // Retrieve the result of the log.
#include <mutex>   // Locks the writing to prevent multiple-threads from writing simultaneously.
#include <iomanip> // Printing out the formatted time.
#include <ctime>   // Getting the current time.

//====================
// Pegasus includes
//====================
#include <pegasus/utilities/ipolicy.hpp> // Policy used for print the contents of the logs to different contents.

namespace pegasus
{
	class Logger
	{
	private:
		//====================
		// Member variables
		//====================
		/** The policy that prints the log information to different formats. */
		std::unique_ptr<IPolicy> m_policy;
		/** The stream that stores the result of the current log entry. */
		std::stringstream m_stream;
		/** Prevents multiple threads from writing simultaneously. */
		std::mutex        m_mutex;
		/** Whether info logs are reported. */
		static bool m_infoEnabled;
		/** Whether debug logs are reported. */
		static bool m_debugEnabled;
		/** Whether warning logs are reported. */
		static bool m_warnEnabled;
		/** Whether error logs are reported. */
		static bool m_errorEnabled;

	private:
		//====================
		// Private methods
		//====================
		/**
		* @brief Writes the contents of the log to the message member variable.
		*
		* When all of the log writing has been completed, this method is invoked and the stream is
		* converted to a string and stored in the message member variable. This message is additionally
		* user by Logger classes to commit the message to the different logging formats.
		*/
		void write();

		/**
		* @brief Writes a variable number of arguments to the log.
		*
		* When this method is invoked, it will write a variable number of arguments to the stream. The
		* contents are automatically set to the messages variable upon completion.
		*
		* @param arg  The first argument.
		* @param args The additional arguments.
		*/
		template <typename Arg, typename... Args>
		void write(Arg&& arg, Args&&... args);

	public:
		//====================
		// Ctors and dtor
		//====================
		/**
		 * @brief Constructor to set the policy for the Logger.
		 *
		 *  Each different instance of the Logger is assigned different policies, the policies
		 *  control how the information that is logged is stored, such as terminals or files. The
		 *  policy is directly related to the lifetime of the Logger object.
		 *   
		 * @param policy The policy interface assigned to the Logger.
		 */
		explicit Logger(std::unique_ptr<IPolicy> policy);

		/**
		 * @brief Default destructor.
		 */
		virtual ~Logger() = default;
		
		//====================
		// Getters and setters
		//====================
		/**
		 * @brief The flag to control where info level messages are pushed to the log.
		 * 
		 * The info flag is set with the subsequent Logging.info_enabled within the configuration
		 * file. The default value for info messaging is false.
		 * 
		 * @param infoEnabled The state to set info level logging to.
		 */
		static void setInfoEnabled(bool infoEnabled);

		/**
		 * @brief The flag to control where debug level messages are pushed to the log.
		 * 
		 * The debug flag is set with the subsequent Logging.debug_enabled within the configuration
		 * file. The default value for debug messaging is false.
		 * 
		 * @param debugEnabled The state to set debug level logging to.
		 */
		static void setDebugEnabled(bool debugEnabled);

		/**
		 * @brief The flag to control where warning level messages are pushed to the log.
		 * 
		 * The warning flag is set with the subsequent Logging.warn_enabled within the configuration
		 * file. The default value for warning messaging is true.
		 * 
		 * @param warnEnabled The state to set warning level logging to.
		 */
		static void setWarningEnabled(bool warnEnabled);

		/**
		 * @brief The flag to control where error level messages are pushed to the log.
		 * 
		 * The error flag is set with the subsequent Logging.error_enabled within the configuration
		 * file. The default value for error messaging is true.
		 * 
		 * @param errorEnabled The state to set error level logging to.
		 */
		static void setErrorEnabled(bool errorEnabled);

		//====================
		// Methods
		//====================
		/**
		 * @brief Prints info level logging to the specified policy.
		 * 
		 * When an info message is printed, it is prefixed with the [INFO] tag.
		 * Information is typically used for information or program flow purposes.
		 *  
		 * @param args The variable number of arguments to push to the log.
		 */
		template <typename... Args>
		void info(Args&&... args);

		/**
		 * @brief Prints debug level logging to the specified policy.
		 * 
		 * When a debug message is printed, it is prefixed with the [DEBUG] tag.
		 * Debug is typically used to print debugging information to the log, such as
		 * shader and script compilation.
		 *  
		 * @param args The variable number of arguments to push to the log.
		 */
		template <typename... Args>
		void debug(Args&&... args);

		/**
		 * @brief Prints warning level logging to the specified policy.
		 * 
		 * When an warning message is printed, it is prefixed with the [WARNING] tag.
		 * Warning messages are typicallly printing when something unexcepted occurs within the
		 * application but does not prevent the program from continuing its primary flow.
		 *  
		 * @param args The variable number of arguments to push to the log.
		 */
		template <typename... Args>
		void warning(Args&&... args);

		/**
		 * @brief Prints error level logging to the specified policy.
		 * 
		 * When an error message is printed, it is prefixed with the [ERROR] tag.
		 * Errors represent extreme circumstances that prevent the application from continuing,
		 * such as a missing Resources.xxx file.
		 *  
		 * @param args The variable number of arguments to push to the log.
		 */
		template <typename... Args>
		void error(Args&&... args);
	};

	//====================
	// Private methods
	//====================
	/**********************************************************/
	template <typename Arg, typename... Args>
	void Logger::write(Arg&& arg, Args&&...args)
	{
		m_stream << arg << " ";
		this->write(args...);
	}

	//====================
	// Methods
	//====================
	/**********************************************************/
	template <typename... Args>
	void Logger::info(Args&&... args)
	{
		m_mutex.lock();

		auto time = std::time(nullptr);
		auto tm = std::localtime(&time);

		this->write("[INFO]:", std::put_time(tm, "%H:%M:%S"), "-", args...);

		m_mutex.unlock();
	}

	/**********************************************************/
	template <typename... Args>
	void Logger::debug(Args&&... args)
	{
		m_mutex.lock();
		
		auto time = std::time(nullptr);
		auto tm = std::localtime(&time);

		this->write("[DEBUG]:", std::put_time(tm, "%H:%M:%S"), "-", args...);

		m_mutex.unlock();
	}

	/**********************************************************/
	template <typename... Args>
	void Logger::warning(Args&&... args)
	{
		m_mutex.lock();

		auto time = std::time(nullptr);
		auto tm = std::localtime(&time);

		this->write("[WARNING]:", std::put_time(tm, "%H:%M:%S"), "-", args...);

		m_mutex.unlock();
	}

	/**********************************************************/
	template <typename... Args>
	void Logger::error(Args&&... args)
	{
		m_mutex.lock();
		
		auto time = std::time(nullptr);
		auto tm = std::localtime(&time);

		this->write("[ERROR]:", std::put_time(tm, "%H:%M:%S"), "-", args...);

		m_mutex.unlock();
	}

} // namespace pegasus

#endif//_PEGASUS_LOGGER_HPP_
