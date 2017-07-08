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
#include <fstream> // Loading and populating a stream with a file from disk.

//==================== 
// Sparky includes
//==================== 
#include <sparky/utilities/file_reader.hpp> // Class declaration.

namespace sparky
{
	//==================== 
	// Ctors and dtor
	//==================== 
	/**********************************************************/
	FileReader::FileReader()
		: Reader(), m_source()
	{
		// Empty.
	}
	
	/**********************************************************/
	FileReader::FileReader(const std::string& filename)
		: Reader(), m_source()
	{
		this->open(filename);
	}
	
	//==================== 
	// Getters and setters
	//==================== 
	const std::string& FileReader::getSource() const
	{
		return m_source;
	}

	//==================== 
	// Methods
	//==================== 
	/**********************************************************/
	void FileReader::open(const std::string& filename) // override.
	{
		// Open the file.
		std::ifstream file;
		file.open(filename, std::ios::in | std::ios::binary);
		
		// The file failed to open, set the failed state and close the stream.
		if (file.fail())
		{
			m_failed = true;
			file.close();
			
			return;
		}
		
		// The file succeeded, set the entire contents into the source string. 
		m_source.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
		// The file did not fail to load.
		m_failed = false;
		// Ensure the stream has been closed.
		file.close();
	}
	
} // namespace sparky