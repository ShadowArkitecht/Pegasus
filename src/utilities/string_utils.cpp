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
// C++ includes
//====================
#include <algorithm> // Lambda methods.
#include <cctype> // Checking if a character only contains white-space.

//====================
// Pegasus includes
//====================
#include <pegasus/utilities/string_utils.hpp> // Class declaration.

namespace pegasus
{
	//====================
	// Methods
	//====================
	/**********************************************************/
	std::string StringUtils::leftTrim(const std::string& str)
	{
		std::string s = str;
		s.erase(std::begin(s), std::find_if(std::begin(s), std::end(s), [](int ch) {
			return !std::isspace(ch);
		}));

		return s;
	}

	/**********************************************************/
	std::string StringUtils::rightTrim(const std::string& str)
	{
		std::string s = str;
		s.erase(std::find_if(std::rbegin(s), std::rend(s), [](int ch) {
			return !std::isspace(ch);
		}).base(), std::end(s));

		return s;
	}

	/**********************************************************/
	std::string StringUtils::trim(const std::string& str)
	{
		std::string s = StringUtils::leftTrim(str);
		s = StringUtils::rightTrim(s);

		return s;
	}

} // namespace pegasus
