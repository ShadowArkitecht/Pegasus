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
#include <pegasus/utilities/stream_reader.hpp> // Class declaration.

namespace pegasus
{
	//==================== 
	// Ctors and dtor
	//==================== 
	/**********************************************************/
	StreamReader::StreamReader()
		: Reader(), m_file(), m_line()
	{
		// Empty.
	}
	
	/**********************************************************/
	StreamReader::StreamReader(const std::string& filename)
		: Reader(), m_file(), m_line()
	{
		this->open(filename);
	}

	/**********************************************************/
	StreamReader::~StreamReader()
	{
		m_file.close();
	}

	//==================== 
	// Getters and setters
	//==================== 
	/**********************************************************/
	std::istream& StreamReader::hasNext()
	{
		return std::getline(m_file, m_line);
	}

	/**********************************************************/
	const std::string& StreamReader::getLine() const
	{
		return m_line;
	}

	//==================== 
	// Methods
	//==================== 
	/**********************************************************/
	void StreamReader::open(const std::string& filename) // override
	{
		m_file.open(filename);
		if (m_file.fail())
		{
			m_failed = true;
			return;
		}

		m_failed = false;
	}

} // namespace pegasus
