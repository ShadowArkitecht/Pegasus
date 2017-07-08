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

#ifndef _SPARKY_STRING_UTILS_HPP_
#define _SPARKY_STRING_UTILS_HPP_

//====================
// C++ includes
//====================
#include <string>

namespace sparky
{
	class StringUtils final
	{
	public:
		//====================
		// Methods
		//====================
		/**
		 * @brief Trims all white-space characters on the left-hand side of a string and returns the result.
		 *
		 * @returns A string object with no white-space on the left-hand side.
		 */
		static std::string leftTrim(const std::string& str);

		/**
		* @brief Trims all white-space characters on the right-hand side of a string and returns the result.
		*
		* @returns A string object with no white-space on the right-hand side.
		*/
		static std::string rightTrim(const std::string& str);

		/**
		* @brief Trims all white-space characters on both sides of a string and returns the result.
		*
		* @returns A string object with no white-space on either side.
		*/
		static std::string trim(const std::string& str);
	};

} // namespace sparky

#endif//_SPARKY_STRING_UTILS_HPP_