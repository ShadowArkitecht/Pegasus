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

#ifndef _PEGASUS_FILE_READER_HPP_
#define _PEGASUS_FILE_READER_HPP_

//==================== 
// Pegasus includes
//==================== 
#include <pegasus/utilities/reader.hpp>

namespace pegasus
{
	/**
	 * @author Benjamin Carter
	 * 
	 * @class pegasus::FileReader
	 * @ingroup utilities
	 * 
	 * @brief IO class responsible for loading and storing the entire contents of an external file.
	 * 
	 * The FileReader class is one of the child Reader classes supported within the Pegasus Engine. The file
	 * reader will read the entirety of a specified file into memory and store it within a single string object.
	 * This is convenient for files that do not require precision or runtime checks upon each individual line of the 
	 * file, such as loading and compiling glsl shaders.
	 * 
	 * If the user needs to read each line of a file individually, it best to use the provided StreamReader class. 
	 */
	class FileReader final : public Reader
	{
	private:
		/** Stores the result of the open method. */
		std::string m_source;

	public:
		//==================== 
		// Ctors and dtor
		//==================== 
		/**
		 * @brief Default constructor for the FileReader.
		 * 
		 * The default constructor will call the parent constructor and initialise all of the member 
		 * variables to default values.
		 */
		explicit FileReader();
		
		/**
		 * @brief Constructor that will read in a file upon instantiation.
		 * 
		 * When this constructor is invoked, it will implicitly use the overriden open method to open and 
		 * parse the specified file. If the file failed to parse, the state is set to failed and file stream
		 * will close.
		 *
		 * @param filename The file on disk to open and read.
		 */
		explicit FileReader(const std::string& filename);
		
		/**
		 * @brief Default destructor.
		 */
		~FileReader() = default;
		
		//==================== 
		// Getters and setters
		//==================== 
		/**
		* @brief Retrieves the source of the reader.
		*
		* The source refers to the loaded in contents of the file that is opened when the open method
		* is invoked. If the open method failed to find the file, the string is empty.
		*
		* @returns The source of the Reader object.
		*/
		const std::string& getSource() const;

		//==================== 
		// Methods
		//==================== 
		/**
		 * @brief Reads in a file from disk and stores the result in a single string instance.
		 * 
		 * When the file is opened, it is first checked that it opened successfully. If the file opened
		 * with no issues the contents of the file are copied into the source member variable, which can be
		 * queried with the Reader::getSource() method. 
		 * 
		 * If the file failed to load, the stream will be closed and the reader state will be set to failed.
		 * 
		 * @param filename The file to open and read from disk.
		 */
		void open(const std::string& filename) override;
	};
	
} // namespace pegasus

#endif//_PEGASUS_FILE_READER_HPP_
