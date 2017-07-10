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

#ifndef _SPARKY_CONFIG_FILE_HPP_
#define _SPARKY_CONFIG_FILE_HPP_

//====================
// C++ includes
//====================
#include <unordered_map> // Stores variables and their subsequent values.
#include <string>        // Storing the variable and value.

namespace sparky
{
	class ConfigFile final
	{
	private:
		//====================
		// Member variables
		//====================
		/** The variables are stored in a look-up table. */
		std::unordered_map<std::string, std::string> m_variables;

	private:
		//====================
		// Private methods
		//====================
		/**
		 * @brief Provides additional checks to the variable and parses it.
		 *
		 * This method will check that each individual line within the configuration
		 * file is properly formatted and structured. This method is only invoked when
		 * a variable or type is discovered on the currently parsing line. This method
		 * will provide additional checks and only add the variable if all of the
		 * correct structural conditions are met. If the line is not correctly formatted,
		 * an exception is thrown.
		 *
		 * @brief variable     The name of the variable to parse.
		 * @brief datatype     The variables specified datatype.
		 * @brief value        The value attached to the variable.
		 *
		 * @throws runtime_error If any issues are encountered during parsing.
		 */
		void parse(const std::string& variable, const std::string& datatype, const std::string& value);

	public:
		//====================
		// Ctors and dtor
		//====================
		/**
		 * @brief Default constructor for the ConfigFile.
		 */
		explicit ConfigFile();

		/**
		 * @brief Constructor for the ConfigFile which will subsequently load the external configuration file.
		 */
		explicit ConfigFile(const std::string& filename);

		//====================
		// Getters and setters
		//====================
		/**
		 * @brief Retrieves a variable from the configuration file.
		 *
		 * When the user wishes to retrieve a value from the configuration
		 * file, this method can be invoked with the specified datatype. If the
		 * type does not convert to the specified data-type correctly, an undefined
		 * value may be returned. 
		 *
		 * @param variable     The string literal name of the config variable.
		 *
		 * @returns            The value attached to the variable, or an undefined value if not found.
		 */
		template <typename T>
		T get(const std::string& variable) const;

		//====================
		// Methods
		//====================
		/**
		 * @brief Opens and parses the configuration file.
		 *
		 * When the configuration file is opened, it will parse and process
		 * the variables contained within the file and ready them for use
		 * and retrieval. If any errors or formatting issues occur during parsing,
		 * exceptions will be thrown with additional information.
		 *
		 * @param filename     The filename of the configuration file to parse.
		 *
		 * @returns            True if the file parsed successfully.
		 */
		void open(const std::string& filename);
	};

	//====================
	// Getters and setters
	//====================
	/**********************************************************/
	template <>
	int ConfigFile::get<int>(const std::string& variable) const;

	/**********************************************************/
	template <>
	unsigned int ConfigFile::get<unsigned int>(const std::string& variable) const;

	/**********************************************************/
	template <>
	float ConfigFile::get<float>(const std::string& variable) const;

	/**********************************************************/
	template <>
	double ConfigFile::get<double>(const std::string& variable) const;

	/**********************************************************/
	template <>
	std::string ConfigFile::get<std::string>(const std::string& variable) const;

	/**********************************************************/
	template <>
	bool ConfigFile::get<bool>(const std::string& variable) const;

} // namespace sparky

#endif//_SPARKY_CONFIGE_FILE_HPP_