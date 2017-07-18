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

#ifndef _PEGASUS_FILE_POLICY_HPP_
#define _PEGASUS_FILE_POLICY_HPP_

//==================== 
// C++ includes
//====================  
#include <fstream> // Stores and opens a file to stream to.

//==================== 
// Pegasus includes
//====================   
#include <pegasus/utilities/ipolicy.hpp> // Inherits from the IPolicy interface

namespace pegasus
{
	class FilePolicy final : public IPolicy
	{
	private:
		//==================== 
		// Member variables
		//====================  
		/** The file to stream the contents of the log to. */
		std::ofstream m_file;

	public:
		//==================== 
		// Ctors and dtor
		//====================  
		/**
		 * @brief Constructor to open the log and stream content.
		 * 
		 * When this constructor is invoked, it will load and open the 
		 * specified external file and stream the contents of the log to it.
		 * 
		 * @param filename The log file to open and write to.
		 */
		explicit FilePolicy(const std::string& filename);

		/**
		 * @brief Destructor for the FilePolicy
		 * 
		 * The destructor will close the file stream that is retained for writing.
		 */
		virtual ~FilePolicy();

		//==================== 
		// Methods
		//====================  
		/**
		 * @brief Commits the current line from the log to the open file.
		 * 	 
		 * The overriden commit method for the ConsolePolicy object pushes
		 * the current contents of the log to the specified file. 
		 * 
		 * @param msg The message to push to the file.
		 */
		void commit(const std::string& msg) override;
	};

} // namespace pegasus

#endif//_PEGASUS_FILE_POLICY_HPP_
