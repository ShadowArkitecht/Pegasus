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

#ifndef _PEGASUS_CONSOLE_POLICY_HPP_
#define _PEGASUS_CONSOLE_POLICY_HPP_

//==================== 
// Pegasus includes
//====================  
#include <pegasus/utilities/ipolicy.hpp> // Inherits from the IPolicy interface.

namespace pegasus
{
	class ConsolePolicy final : public IPolicy
	{
	public:
		//==================== 
		// Ctors and dtor
		//====================  
		/**
		 * @brief Default constructor for the console policy.
		 */
		explicit ConsolePolicy() = default;

		/**
		 * @brief Default destructor.
		 */
		~ConsolePolicy() = default;

		//==================== 
		// Methods
		//====================  
		/**
		 * @brief Commits the current line from the log to the console.
		 * 	 
		 * The overriden commit method for the ConsolePolicy object pushes
		 * the current contents of the log to the terminal/console. 
		 * 
		 * @param msg The message to push to the console/terminal.
		 */
		void commit(const std::string& msg) override;
	};

} // namespace pegasus

#endif//_PEGASUS_CONSOLE_POLICY_HPP_
