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

//====================
// Pegasus includes
//====================
#include <pegasus/utilities/exceptions/serialize_exception.hpp> // Class declaration.

namespace pegasus
{
	//====================
	// Ctors and dtor
	//====================
	/**********************************************************/
	SerializeException::SerializeException(const char* msg)
		: std::exception(msg)
	{
		// Empty.
	}

	/**********************************************************/
	SerializeException::SerializeException(const std::string& msg)
		: std::exception(msg.c_str())
	{
		// Empty.
	}

	//====================
	// Methods
	//====================
	/**********************************************************/
	const char* SerializeException::what() const
	{
		return std::exception::what();
	}
 
} // namespace pegasus