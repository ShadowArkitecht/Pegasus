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

//====================
// C++ includes
//====================
#include <algorithm> // Removing characters from string with a lambda.
#include <stdexcept> // Throwing runtime_errors.
#include <sstream>   // Streaming the vector values.

//====================
// Sparky includes
//====================
#include <sparky/core/config_file.hpp>        // Class declarations.
#include <sparky/utilities/stream_reader.hpp> // Reading in the configuration file.
#include <sparky/utilities/string_utils.hpp>  // Trimming strings.

namespace sparky
{
	//====================
	// Ctors and dtor
	//====================
	/**********************************************************/
	ConfigFile::ConfigFile()
		: m_variables()
	{
	}

	/**********************************************************/
	ConfigFile::ConfigFile(const std::string& filename)
		: m_variables()
	{
		this->open(filename);
	}

	//====================
	// Getters and setters
	//====================
	/**********************************************************/
	template <>
	int ConfigFile::get<int>(const std::string& variable) const
	{
		return std::stoi(m_variables.at(variable));
	}

	/**********************************************************/
	template <>
	unsigned int ConfigFile::get<unsigned int>(const std::string& variable) const
	{
		return std::stoi(m_variables.at(variable));
	}

	/**********************************************************/
	template <>
	float ConfigFile::get<float>(const std::string& variable) const
	{
		return std::stof(m_variables.at(variable));
	}

	/**********************************************************/
	template <>
	double ConfigFile::get<double>(const std::string& variable) const
	{
		return std::stod(m_variables.at(variable));
	}

	/**********************************************************/
	template <>
	std::string ConfigFile::get<std::string>(const std::string& variable) const
	{
		return m_variables.at(variable);
	}

	/**********************************************************/
	template <>
	bool ConfigFile::get<bool>(const std::string& variable) const
	{
		return m_variables.at(variable) == "true";
	}

	/**********************************************************/
	template <> 
	glm::ivec2 ConfigFile::get<glm::ivec2>(const std::string& variable) const
	{
		std::stringstream ss(m_variables.at(variable));
		std::vector<std::string> elements;

		while (ss.good())
		{
			std::string element;
			std::getline(ss, element, ',');
			elements.push_back(element);
		}
		
		return glm::ivec2(std::stoi(elements.at(0)), std::stoi(elements.at(1)));
	}

	//==================== 
	// Private methods
	//====================
	/**********************************************************/
	void ConfigFile::parse(const std::string& variable, const std::string& datatype, const std::string& value)
	{
		auto isDigit = [](const std::string& value) -> bool {
			return value.find_first_not_of("-.0123456789") == std::string::npos;
		};

		if (datatype == "int" || datatype == "uint" || datatype == "float" || datatype == "double")
		{
			if (!isDigit(value))
			{
				throw std::runtime_error(variable + " of datatype " + datatype + " is not a numerical value.");
			}

			m_variables.insert({ variable, value });
		}
		else if (datatype == "string")
		{
			if (value.at(0) != '"' && value.at(value.length() - 1) != '"')
			{
				throw std::runtime_error(variable + " is not a correctly formatted string.");
			}

			m_variables.insert({ variable, value.substr(1, value.length() - 2) });
		}
		else if (datatype == "boolean")
		{
			if (value != "true" && value != "false")
			{
				throw std::runtime_error(variable + " is not a correctly formatted boolean value.");
			}

			m_variables.insert({ variable, value });
		}
		else if (datatype.substr(0, 4) == "vec2")
		{
			if (value.at(0) != '(' && value.at(value.length() - 1) != ')')
			{
				throw std::runtime_error(variable + "is not a correctly formatted vec2 value.");
			}

			m_variables.insert({ variable, value.substr(1, value.length() - 2 )});
		}
		else
		{
			throw std::runtime_error(variable + " does not conform to a defined datatype.");
		}
	}

	//====================
	// Methods
	//====================
	/**********************************************************/
	void ConfigFile::open(const std::string& filename)
	{
		// TODO: Check for extension.
		StreamReader reader(filename);
		if (reader.failed())
		{
			// TODO: Throw an exception.
			throw std::runtime_error("Failed to open StreamReader for configuration file: " + filename);
		}

		// Sections are used to divide the config file up into different chunks.
		std::string section;
		while (reader.hasNext())
		{
			// Retrieve the currently read line.
			std::string line = reader.getLine();
			// Remove all unnecessary characters and trailing returns.
			line.erase(std::remove_if(std::begin(line), std::end(line), [](char c) {
				return c == '\r' || c == '\n' || c == '\t';
			}));
			// Left trim all the whitespace off the line.
			line = StringUtils::leftTrim(line);

			// If the line is empty or a comment, just ignore it.
			if (line.empty() || line.at(0) == '#')
			{
				continue;
			}
			// Check if the line is a section declaration.
			if (line.at(0) == '[' && line.at(line.length() - 1) == ']')
			{
				section = line.substr(1, line.length() - 2);
				continue;
			}

			// Find the indices of the type declaration and assignment.
			std::size_t typeIndex = line.find(':');
			std::size_t assignIndex = line.find('=');
			// The line was not in the expected format, throw an exception.
			if (typeIndex == std::string::npos || assignIndex == std::string::npos)
			{
				throw std::runtime_error("Incorrectly formatted line.");
			}

			// Grab the variable declaration.
			std::string variable = line.substr(0, typeIndex);
			// trim the whitespace off the end of the variable.
			variable = StringUtils::rightTrim(variable);
			// If the section isn't empty, concat the section and variable together.
			if (!section.empty())
			{
				variable = section + "." + variable;
			}

			// Retrieve and trim the data-type.
			std::string datatype = StringUtils::trim(line.substr(typeIndex + 1, assignIndex - typeIndex - 1));
			// Retrieve and trim the value.
			std::string value = StringUtils::trim(line.substr(assignIndex + 1, line.length()));
			// Parse the variable.
			this->parse(variable, datatype, value);
		}
	}

	/**********************************************************/
	void ConfigFile::close()
	{
		// Clear all of the retained variables.
		m_variables.clear();
	}

} // namespace sparky