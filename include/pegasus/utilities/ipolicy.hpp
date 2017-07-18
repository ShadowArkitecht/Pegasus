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

#ifndef _PEGASUS_IPOLICY_HPP_
#define _PEGASUS_IPOLICY_HPP_

//==================== 
// C++ includes
//====================  
#include <string> // Committing a log line to the policy.

namespace pegasus
{
	class IPolicy
	{
	public:
		//==================== 
		// Ctors and dtor
		//====================  
		/**
		 * @brief Default constructor.
		 */
		explicit IPolicy() = default;

		/**
		 * @brief Default destructor.
		 */
		virtual ~IPolicy() = default;

		//==================== 
		// Methods
		//====================  
		/**
		 * @brief Commits the changes to the log to the chosen format.
		 * 
		 * This method is overriden by any class that inherits from it.
		 * The commit method is called after any additional information is pushed
		 * to the log, the commit will when process the message and push it to the
		 * chosen policy format (the terminal, files etc).
		 * 
		 * @param msg The message to commit to the policy.
		 */
		virtual void commit(const std::string& msg) = 0;
	};

} // namespace pegasus

#endif//_PEGASUS_IPOLICY_HPP_
